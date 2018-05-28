trap 'kill %1' SIGINT
./jobs/runFitsProfiledChannel.sh ele & ./jobs/runFitsProfiledChannel.sh mu
./jobs/runFitsProfiledChannel.sh ele,mu
