#!/bin/bash

# install npm
if ! command -v npm &> /dev/null; then
    echo "npm command not found. Installing npm..."
    sudo apt install npm tmux -y
fi

if [ ! -d "node_modules" ]; then
    echo "node_modules directory does not exist. Initializing the project..."
    npm init -y
    npm install express
    npm install chart.js

fi


if ! sudo ufw status | grep -q '3000'; then
    sudo ufw allow 3000
    sudo ufw allow 5120
fi
 
# avvia il sito web
tmux new-session -d -s npm_session 'npm start'
tmux new-session -d -s python_session 'python3 server.py'
