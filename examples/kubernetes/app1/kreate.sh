#!/bin/bash
cd "$(dirname "$0")"

export APP=app1
#APP_REPLICAS=1
#APP_CPU_LIMIT=500m
#APP_MEMORY_LIMIT=512Mi

export APP_LABELS="use-db=enabled use-ext-app8=enabled"

../lib/deployment.sh
../lib/service.sh
../lib/ingress.sh
