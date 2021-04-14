#!/bin/bash

FILE=$APP-service.yaml
$KREATE_FILE

cat >$FILE  <<EOF
kind: Service
apiVersion: v1
metadata:
  name: $APP-service
spec:
  selector:
    app: $APP
  ports:
  - protocol: TCP
    port: 8080
    targetPort: 8080
EOF
$KREATE_DONE
