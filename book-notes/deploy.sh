REMOTE_SERVER=dramaticanalysis
BUILD_FILENAME=build.tar.gz
KEYFILE_PATH=~/.ssh/aws-general.pem
REMOTE_SCRIPT=/home/ubuntu/remote-deploy.sh

cd src
COPYFILE_DISABLE=1 tar -czvf ${BUILD_FILENAME} *
scp -i ${KEYFILE_PATH} ./${BUILD_FILENAME} ubuntu@${REMOTE_SERVER}:
ssh -i ${KEYFILE_PATH} -tt ubuntu@${REMOTE_SERVER} "sudo ${REMOTE_SCRIPT}"
cd ..
