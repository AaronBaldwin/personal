REMOTE_SERVER=dramaticanalysis
KEYFILE_PATH=~/.ssh/aws-general.pem
REMOTE_SCRIPT=/home/ubuntu/remote-deploy-books.sh

if [ -z "$1" ]
  then echo "usage: ./deploy-books [filepath]; copies the text file in [filepath] to dramaticanalysis.com" && exit 1;
fi

filename=$(eval echo $1 | cut -d"/" -f2)
bookname=$(eval echo $1 | cut -d"/" -f1)

scp -i ${KEYFILE_PATH} ./books/${1} ubuntu@${REMOTE_SERVER}:
ssh -i ${KEYFILE_PATH} -tt ubuntu@${REMOTE_SERVER} "sudo ${REMOTE_SCRIPT} ${bookname} ${filename}"
