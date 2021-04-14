#!/bin/bash

source "$(dirname "$0")"/functions.sh

APP_CPU_LIMIT=${APP_CPU_LIMIT-500m}
APP_MEMORY_LIMIT=${APP_MEMORY_LIMIT-512Mi}

FILE=$APP-deployment.yaml
$KREATE_FILE

cat >$FILE <<EOF
kind: Deployment
apiVersion: apps/v1
metadata:
  name: $APP
spec:
  replicas: ${APP_REPLICAS-1}
  selector:
    matchLabels:
      app: $APP
  template:
    metadata:
      name: $APP
      labels:$(labels)
        app: $APP
      annotations:
        app.kubernetes.io/name: $APP
        #app.kubernetes.io/instance:
        app.kubernetes.io/version: $APP_VERSION
        app.kubernetes.io/component: webservice
        app.kubernetes.io/part-of: kubernetes-example
        app.kubernetes.io/managed-by: kreate
    spec:
      volumes:
      - name: app-files
        configMap:
          name: $APP-files
      containers:
      - name: tomcat
        image: $APP_IMAGE:$APP_VERSION
        imagePullPolicy: Always
        envFrom:
        - secretRef:
            name: $APP-secrets
        - configMapRef:
            name: shared-vars
        ports:
        - containerPort: 8080
          protocol: TCP
        volumeMounts:
          - name: app-files
            mountPath: /home/spring/application.yaml
            subPath: application.yaml
        resources:
          limits:
            cpu: ${APP_CPU_LIMIT}
            memory: ${APP_MEMORY_LIMIT}
          requests:
            cpu: ${APP_CPU_LIMIT}
            memory: ${APP_MEMORY_LIMIT}
      #restartPolicy: Never
EOF
$KREATE_DONE
