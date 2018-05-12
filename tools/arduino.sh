#!/bin/bash - 
#===============================================================================
#
#          FILE: arduino.sh
# 
#         USAGE: ./arduino.sh 
# 
#   DESCRIPTION: 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: YOUR NAME (), 
#  ORGANIZATION: 
#       CREATED: 05/09/2018 12:15
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

#!/bin/bash
# Starts the Arduino IDE using the docker image.
# see also: ...

#    -v /dev/ttyACM0:/dev/ttyACM0 \
#    -v /dev/ttyUSB0:/dev/ttyUSB0 \
docker run \
    -it \
    --rm \
    --network=host \
    --privileged \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v /dev:/dev \
    -v $HOME/topics:/topics \
    -v $HOME/topics/arduino:/home/developer/Arduino \
    --name arduino \
    nola_con_2018_badge \
    arduino
