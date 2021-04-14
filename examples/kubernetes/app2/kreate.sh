#!/bin/bash
cd "$(dirname "$0")"

export APP=app2
APP_REPLICAS=3
APP_CPU_LIMIT=1000m
APP_MEMORY_LIMIT=1024Mi

export APP_LABELS="use-db=enabled"

../lib/deployment.sh
../lib/service.sh
../lib/ingress.sh
