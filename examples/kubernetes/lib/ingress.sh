#!/bin/bash

FILE=$APP-ingress.yaml
$KREATE_FILE

cat >$FILE  <<EOF
kind: Ingress
apiVersion: networking.k8s.io/v1beta1
metadata:
  name: $APP-ingress
spec:
  rules:
    - host: $APP.example.kisst.org
      http:
        paths:
          - backend:
              serviceName: $APP-service
              servicePort: 8080
EOF
$KREATE_DONE
