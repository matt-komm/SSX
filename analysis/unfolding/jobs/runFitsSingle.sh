trap 'kill %1' SIGINT
./jobs/runFitsSingleChannel.sh ele & ./jobs/runFitsSingleChannel.sh mu
./jobs/runFitsSingleChannel.sh ele,mu
