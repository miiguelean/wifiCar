<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Car Control</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<div class="title">ESP32<br>Car Control</div>
    <div class="controller-top">
        <form method="GET" action="http://192.168.1.12/forward">
            <button type="submit">↑</button>
        </form>
    </div>
    <div class="controller-middle">
        <form method="GET" action="http://192.168.1.12/left">
            <button type="submit">←</button>
        </form>
        <form class="cm2" method="GET" action="http://192.168.1.12/stop">
            <button type="submit">Stop</button>
        </form>
        <form method="GET" action="http://192.168.1.12/right">
            <button type="submit">→</button>
        </form>
    </div>   
    <div class="controller-bottom">
        <form method="GET" action="http://192.168.1.12/backward">
            <button type="submit">↓</button>
        </form>
    </div>
    <form class="form-data" method="GET" action="grafica.php">
            <button class="btn-data" type="submit">Ver Datos</button>
    </form>
    <div class="footer">By El Store y Alvarin</div>
</body>
</html>