TARGET_DIRECTORY=/var/www/html/booknotes
BUILD_FILENAME=build.tar.gz  

mv ./${BUILD_FILENAME} ${TARGET_DIRECTORY}
cd $TARGET_DIRECTORY
tar -xzf ${BUILD_FILENAME}
