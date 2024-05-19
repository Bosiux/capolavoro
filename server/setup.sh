###### Script per sistemi basati su debian ######

# install npm
sudo apt install npm -y

# inizializza il progetto
npm init -y

# installa librerie express e chart
npm install express
npm install chart.js


# aprire la porta 3000 del firewall
sudo ufw allow 3000 
 
# avvia il sito web
node server.js
