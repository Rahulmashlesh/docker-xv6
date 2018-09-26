##Shell script to automate the build and run process

#Build the docker image
sudo docker build -t xv6 .

#Run the docker image
sudo docker run -it xv6 bash

