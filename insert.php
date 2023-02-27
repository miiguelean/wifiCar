<?php
// Conexión a la base de datos
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "ultrasonico";

$conn = new mysqli($servername, $username, $password, $dbname);

// Verifica la conexión
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Obtiene el valor enviado por el ESP32
$valor = $_GET['valor'];

// Agrega el valor a la base de datos
$sql = "INSERT INTO status (fecha, valor) VALUES (NOW(), '$valor')";
if ($conn->query($sql) === TRUE) {
  echo "Dato agregado correctamente";
} else {
  echo "Error al agregar dato: " . $conn->error;
}

$conn->close();
?>
