// Obtener la etiqueta canvas y su contexto
var pirCanvas = document.getElementById("pirChart");
var pirCtx = pirCanvas.getContext('2d');

// Obtener los datos del sensor PIR a través de una petición AJAX
var xhttp = new XMLHttpRequest();
xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        var pirData = JSON.parse(this.responseText);
        // Configurar la gráfica
        var pirChart = new Chart(pirCtx, {
            type: 'line',
            data: {
                labels: pirData.map(function(d) { return d[0]; }),
                datasets: [{
                    label: 'Sensor Ultrasonico',
                    data: pirData.map(function(d) { return d[1]; }),
                    borderColor:'#1091D2',
                    fill: false
                }]
            },
            options: {
                responsive: true,
                maintainAspectRatio: false,
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: true,
                            max: 1
                        }
                    }]
                },
                // Agregar la siguiente línea para cambiar el color del texto
                legend: {
                    labels: {
                        fontColor: '#1091D2'
                    }
                }
            }
        });
    }
};
xhttp.open("GET", "datos.php", true);
xhttp.send();
pirCanvas.resize();