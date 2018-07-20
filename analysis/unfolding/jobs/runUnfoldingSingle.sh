trap 'kill %1' SIGINT
./jobs/runUnfoldingSingleChannel.sh ele & ./jobs/runUnfoldingSingleChannel.sh mu
./jobs/runUnfoldingSingleChannel.sh ele,mu
