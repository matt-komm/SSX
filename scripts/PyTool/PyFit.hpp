#ifndef __PYFIT_H__
#define __PYFIT_H__

#include "TObject.h"
#include "TH1.h"
#include "TH1F.h"
#include "TH2.h"
#include "TH2F.h"
#include "TF1.h"
#include "TMath.h"

#include "Math/Minimizer.h"
#include "Math/Factory.h"
#include "Math/Functor.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <limits>

namespace PyFit
{

template <typename T> typename std::enable_if<std::is_signed<T>::value, int>::type inline constexpr signum(T x) {
    return T(0) < x;  
}

class Parameter
{
    private:
        std::string _name;
        double _scaleFactor;
        double _unc;
        
        double _min;
        double _max;
        
        double _priorMean;
        double _priorWidth;
    public:
        Parameter(const char* name):
            _name(name),
            _scaleFactor(1.0),
            _unc(-1),
            _min(std::numeric_limits<float>::lowest()),
            _max(std::numeric_limits<float>::max()),
            _priorMean(1.0),
            _priorWidth(10000)
        {
        }
        
        void setUncertainty(double unc)
        {
            _unc = unc;
        }
        
        double getMin() const
        {
            return _min;
        }
        
        double getMax() const
        {
            return _max;
        }
        
        double getUncertainty() const
        {
            return _unc;
        }
        
        inline std::string getName() const
        {
            return _name;
        }
        
        void setPrior(double mean, double width)
        {
            _priorMean=mean;
            _priorWidth=width;
        }
                        
        void setLimits(double min, double max)
        {
            _min=min;
            _max=max;
        }
        
        double setScaleFactor(double scaleFactor)
        {
            return _scaleFactor = scaleFactor;
        }
        
        double nll()
        {
            if (std::isnan(_scaleFactor))
            {
                return std::numeric_limits<double>::max();
            }
            return 1.0;//0.5*(_scaleFactor-_priorMean)*(_scaleFactor-_priorMean)/_priorWidth/_priorWidth;
        }
        
        double getScaleFactor() const
        {
            return _scaleFactor;
        }
        
        virtual ~Parameter()
        {
        }
        
    ClassDef(PyFit::Parameter, 1)
};

class Prediction
{
    public:
        std::vector<double> entries;
        std::vector<double> uncertainty2;
        
        Prediction(unsigned int N):
            entries(N,0),
            uncertainty2(N,0)
        {
        }
        Prediction& operator+=(const Prediction& p)
        {
            if (entries.size()!=p.entries.size())
            {
                throw std::runtime_error("attempting to add predictions with different sizes");
            }
            if (uncertainty2.size()!=p.uncertainty2.size())
            {
                throw std::runtime_error("attempting to add predictions with different sizes");
            }
            for (unsigned int i = 0; i < entries.size(); ++i)
            {
                entries[i]+=p.entries[i];
                uncertainty2[i]+=p.uncertainty2[i];
            }
            return *this;
        }
        
        void toRootHistogram(TH1* hist) const
        {
            if (entries.size()!=hist->GetNbinsX())
            {
                throw std::runtime_error("target histogram has not the same number of bins as prediction");
            }
            for (unsigned int i = 0; i < entries.size(); ++i)
            {
                hist->SetBinContent(i+1,entries[i]);
                hist->SetBinError(i+1,std::sqrt(uncertainty2[i]));
            }
        }
        
        virtual ~Prediction()
        {
        }
        
    ClassDef(PyFit::Prediction, 1)
};



class Component
{
    public:
        virtual void queryParameters(std::map<std::string, PyFit::Parameter*>& parameters) const = 0;
        virtual void getPrediction(Prediction* p) const = 0;
        virtual int getNbins() const = 0;
        
        virtual ~Component()
        {
        }
        
};



class ConstShapeComponent:
    public Component
{
    private:   
        TH1* _hist; 
        std::vector<PyFit::Parameter*> _parameters; //!
    public: 
        ConstShapeComponent(TH1* hist):
            _hist((TH1*)hist->Clone())
        {
            _hist->SetDirectory(0);
        }
        
        virtual int getNbins() const
        {
            return _hist->GetNbinsX();
        }
        
        void addSFParameter(PyFit::Parameter* parameter)
        {
            _parameters.push_back(parameter);
        }
        
        virtual void queryParameters(std::map<std::string, PyFit::Parameter*>& parameters) const
        {
            for (PyFit::Parameter* parameter: _parameters)
            {
                parameters[parameter->getName()]=parameter;
            }
        }
        
        virtual void getPrediction(Prediction* p) const
        {
            if ((int)p->entries.size()!=_hist->GetNbinsX())
            {
                throw std::runtime_error("histogram in component has different number of bins");
            }
            double combinedSF = 1.0;
            for (const PyFit::Parameter* parameter: _parameters)
            {
                combinedSF*=parameter->getScaleFactor();
            }
            for (unsigned int i = 0; i < p->entries.size(); ++i)
            {
                p->entries[i]+=combinedSF*_hist->GetBinContent(i+1);
                p->uncertainty2[i]+=combinedSF*combinedSF*_hist->GetBinError(i+1)*_hist->GetBinError(i+1);
            }
            
            
        }
        
        virtual ~ConstShapeComponent()
        {
            delete _hist;
        }
    ClassDef(PyFit::ConstShapeComponent, 1)
};



class Observable
{
    private:
        std::vector<PyFit::Component*> _components; //!
        TH1* _data;
        std::vector<double> _beta;
        
    public:
        Observable(TH1* data):
            _data(data),
            _beta(data->GetNbinsX())
        {
        }
        
        void getPrediction(Prediction* p)
        {
            for (PyFit::Component* component: _components)
            {
                component->getPrediction(p);
            }
        }
        
        
        void addComponent(PyFit::Component* component)
        {
            if (component->getNbins()!=_data->GetNbinsX())
            {
                throw std::runtime_error("Data ("+std::to_string(_data->GetNbinsX())+") and prediction ("+std::to_string(component->getNbins())+") have different binning");
            }
            _components.push_back(component);
        }
        
        void queryParameters(std::map<std::string, PyFit::Parameter*>& parameters) const
        {
            for (PyFit::Component* comp: _components)
            {
                comp->queryParameters(parameters);
            }
        }
        
        void initFit()
        {
            for (unsigned int i = 0; i < _beta.size(); ++i)
            {
                _beta[i]=0.0001;
            }
        }
        
        double nll(bool useBB=false)
        {   
            Prediction prediction(_data->GetNbinsX());
            this->getPrediction(&prediction);
            
            double nll = 0;
            for ( int ibin = 0; ibin < _data->GetNbinsX(); ++ibin)
            {
                const double d = _data->GetBinContent(ibin+1);
                const double unc = std::sqrt(std::max(0.0,prediction.uncertainty2[ibin]));
                const double p_raw = prediction.entries[ibin];
                double p = p_raw;
                
                
               
                if (useBB and unc>0.0)
                {
                    const double unc2 = unc*unc;
                    const double unc4 = unc2*unc2;
                    
                    //guess beta by locally minimizing the likelihood wrt beta
                    const double best_beta = 0.5*(-unc2-p_raw+std::sqrt(unc4-2*unc2*p_raw+p_raw*p_raw+4*d*unc2))/unc;
                    _beta[ibin]=best_beta;
                    nll-=0.5*_beta[ibin]*_beta[ibin]; //gaussian prior
                    p += unc*_beta[ibin];
                    //printf("beta=%6.4f",_beta[ibin]);
                }

                //using log of poisson distribution: x*log(lambda)-lambda
                //skip bins with no prediction
                if (p > 0.0)
                {
                     if (d > 0.0)
                     {
                         nll -= d * std::log(p)-p;
                     }
                 }
                 else if (d > 0.0)
                 {
                     return std::numeric_limits<double>::max();
                 }
            }
            return nll;
        }
        
        virtual ~Observable()
        {
        }
        
    
};


        
class MLFit
{
    private:
        std::vector<PyFit::Observable*> _observables; //!
        std::vector<PyFit::Parameter*> _parameters;
       
        std::shared_ptr<TH2F> _correlations;
        
        bool _useBB;
        
    public:
        MLFit(bool useBB=false):
            _useBB(useBB)
        {
        }
        
        void addObservable(PyFit::Observable* observable)
        {
            _observables.push_back(observable);
        }
        
        void addParameter(PyFit::Parameter* parameter)
        {
            _parameters.push_back(parameter);
        }
        
        double globalNll() const
        {
            double nll = 0.0;
            
            for (auto par: _parameters)
            {
                nll+=par->nll();
            }
            
            for (auto obs: _observables)
            {
                nll+=obs->nll(_useBB);
            }
            
            return nll;
        }
        
        TH2F getCorrelations() const
        {
            return *_correlations.get();
        }
        
        void minimize()
        {
            for (auto obs: _observables)
            {
                obs->initFit();
            }
        
            unsigned int NPar = _parameters.size();
            
            // Choose method upon creation between:
            // kMigrad, kSimplex, kCombined, 
            // kScan, kFumili
            //ROOT::Minuit2::Minuit2Minimizer min ( ROOT::Minuit2::kMigrad );
            std::shared_ptr<ROOT::Math::Minimizer> minimizer(ROOT::Math::Factory::CreateMinimizer("Minuit2", ""));

            minimizer->SetMaxFunctionCalls(10000000);
            minimizer->SetMaxIterations(1000000);
            minimizer->SetTolerance(0.001);
            minimizer->SetPrintLevel(1);
            
            unsigned int iter = 1;

            ROOT::Math::Functor combinedNLLFct(
                [&](const double *x) -> double 
                {
                    //printf("%8i: ",iter);
                    ++iter;
                    for (unsigned int ipar = 0; ipar < NPar; ++ipar)
                    {
                        //printf("%4.2f  ",x[ipar]);
                        _parameters[ipar]->setScaleFactor(x[ipar]);
                        
                    }
                    double chi2 = 2*this->globalNll();
                    //std::cout<<std::endl;
                    return chi2; //chi2 = 2*NLL so that the uncertainty is correctly estimated
                },
                NPar
            );
            
            minimizer->SetFunction(combinedNLLFct);
            
            for (unsigned int ipar = 0; ipar < NPar; ++ipar)
            {
                minimizer->SetVariable(
                    ipar,
                    _parameters[ipar]->getName().c_str(),
                    _parameters[ipar]->getScaleFactor(), 
                    0.01
                );
                minimizer->SetVariableStepSize(
                    ipar,
                    0.01
                );
                /*
                minimizer->SetLimitedVariable(
                    ipar,
                    _parameters[ipar]->getName().c_str(),
                    _parameters[ipar]->getScaleFactor(), 
                    0.01,
                    _parameters[ipar]->getMin(),
                    _parameters[ipar]->getMax()
                );
                */
            }
            minimizer->Minimize();
            
            
            
            _correlations.reset(new TH2F("covariance","",
                _parameters.size(),0,_parameters.size(),
                _parameters.size(),0,_parameters.size()
            ));
            _correlations->SetDirectory(0);
                
            for (unsigned int ipar = 0; ipar < _parameters.size(); ++ipar)
            {
                _parameters[ipar]->setScaleFactor(minimizer->X()[ipar]);
                _parameters[ipar]->setUncertainty(std::sqrt(minimizer->CovMatrix(ipar,ipar)));
                std::cout<<_parameters[ipar]->getName()<<": "<<minimizer->X()[ipar]<<" +- "<<minimizer->Errors()[ipar]<<std::endl;
                
                _correlations->GetXaxis()->SetBinLabel(ipar+1,_parameters[ipar]->getName().c_str());
                _correlations->GetYaxis()->SetBinLabel(ipar+1,_parameters[ipar]->getName().c_str());
                
                
            }
            
            for (unsigned int ipar = 0; ipar < _parameters.size(); ++ipar)
            {
                printf("%20s: ",_parameters[ipar]->getName().c_str());
                for (unsigned int jpar = 0; jpar < _parameters.size(); ++jpar)
                {
                    _correlations->SetBinContent(ipar+1,jpar+1,minimizer->Correlation(ipar,jpar));
                    printf("%+05.3f ",minimizer->Correlation(ipar,jpar));
                }
                std::cout<<std::endl;
            }
            /*
            for (auto obsDataPair: _observableDataPairs)
            {
                const std::vector<float>& betas = obsDataPair.first->getBB();
                for (unsigned int ibb = 0; ibb < betas.size(); ++ibb)
                {
                    std::cout<<ibb<<": "<<betas[ibb]<<std::endl;
                }
            }
            */

        }
        
        virtual ~MLFit()
        {
        }
        
    ClassDef(MLFit, 1)
};


}

#endif
