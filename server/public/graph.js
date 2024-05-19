
var ctx = document.getElementById('myChart').getContext('2d');
new Chart(ctx, {
    type: 'line',

    data: {
        labels: ['January', 'February', 'March', 'April', 'May', 'June', 'July'],
        datasets: [
            {
            label: 'Umidità',
            backgroundColor: 'rgba(255, 99, 132, 0.2)', // Fill color with alpha (opacity)
            borderColor: '#4DB6AC',
            data: [0, 10, 5, 2, 20, 30, 45]
            },
            {
                label: 'Temperatura',
                backgroundColor: 'rgba(255, 99, 132, 0.2)', // Fill color with alpha (opacity)
                borderColor: '#B71C1C',
                data: [26, 25, 26.2, 28, 24, 26.7, 25.9]
            },
            {
                label: 'Acqua',
                backgroundColor: 'rgba(255, 99, 132, 0.2)', // Fill color with alpha (opacity)
                borderColor: '#2196F3',
                data: [15, 15, 14, 13, 21, 15, 15]
            }
        ]
    },

    options: {
        
        elements: {
            line: {
                tension: 0.4 // Adjust the tension to make the lines curved
            }
        }
    }
});




