async function fetchDataFromLocal() {
    try {
        const response = await fetch('./data.csv');
        if (!response.ok) {
            return;
        }
        return await response.text();
    } catch (error) {
        return null;
    }
}

async function generateChartData() {
    const data = await fetchDataFromLocal();
    if (!data) {
        return null;
    }

    const rows = data.split('\n');
    const humidityData = [];
    const temperatureData = [];
    const waterData = [];
    const timeData = [];

    rows.forEach(row => {
        const columns = row.split(',');
        if (columns.length >= 4) { // Ensure at least 4 columns are present (including time)
            let humidity = parseFloat(columns[0]);
            let temperature = parseFloat(columns[1]);
            let water = parseFloat(columns[2]);
            let time = columns[3]; // Assuming time is the 4th column
            if (!isNaN(humidity) && !isNaN(temperature) && !isNaN(water) && water != 0) {
                humidityData.push(humidity);
                temperatureData.push(temperature);
                waterData.push(water);
                timeData.push(time);
            }
        }
    });

    return { humidityData, temperatureData, waterData, timeData };
}


(async () => {
    const ctx = document.getElementById('myChart').getContext('2d');
    
    const { humidityData, temperatureData, waterData, timeData } = await generateChartData();

    if (!humidityData || !temperatureData || !waterData || !timeData) {
        console.error('Failed to generate chart data');
        return;
    }

    var lastTemp = temperatureData[temperatureData.length -1];
    if (lastTemp > 29) {
        var image = document.querySelector('.temperatura-img');
        image.src = './img/warning.png';
    } else {
        var image = document.querySelector('.temperatura-img');
        image.src = './img/accept.png';
    }

    var lastH = humidityData[humidityData.length -1];
    if (lastH < 60) {
        var image = document.querySelector('.umidita-img');
        image.src = './img/warning.png';
    } else {
        var image = document.querySelector('.umidita-img');
        image.src = './img/accept.png';
    }

    var lastW = waterData[waterData.length -1];
    if (lastW < 98) {
        var image = document.querySelector('.acqua-img');
        image.src = './img/warning.png';
    } else {
        var image = document.querySelector('.acqua-img');
        image.src = './img/accept.png';
    }

    

    new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeData,
            datasets: [
                {
                    label: 'Umidità',
                    backgroundColor: 'rgba(255, 99, 132, 0.2)', 
                    borderColor: '#4DB6AC',
                    data: humidityData
                },
                {
                    label: 'Temperatura',
                    backgroundColor: 'rgba(255, 99, 132, 0.2)', 
                    borderColor: '#B71C1C',
                    data: temperatureData
                },
                {
                    label: 'Acqua',
                    backgroundColor: 'rgba(255, 99, 132, 0.2)', 
                    borderColor: 'rgba(33, 150, 243, 0.5)',
                    data: waterData
                }
            ]
        },
        options: {
            elements: {
                line: {
                    tension: 0.4 
                }
            }
        }
    });
})();
