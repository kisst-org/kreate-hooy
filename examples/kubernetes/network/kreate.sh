#!/bin/bash
cd "$(dirname "$0")"

APP=app7 APP_PORT=8080 APP_IP=10.10.10.10 ../lib/egress.sh
APP=app8 APP_PORT=8081 APP_IP=10.10.10.10 ../lib/egress.sh
APP=app9 APP_PORT=8080 APP_IP=10.10.10.11 ../lib/egress.sh
