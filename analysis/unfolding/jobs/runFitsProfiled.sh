trap 'kill %1; kill %2' SIGINT
./jobs/runFitsProfiledChannel.sh ele & ./jobs/runFitsProfiledChannel.sh mu & ./jobs/runFitsProfiledChannel.sh ele,mu
