<?php
// Establecer la conexión con la base de datos
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "ultrasonico";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Obtener los datos del sensor PIR
$sql = "SELECT fecha, valor FROM status";
$result = $conn->query($sql);

$data = array();
while($row = $result->fetch_assoc()) {
    $data[] = array($row["fecha"], $row["valor"]);
}

echo json_encode($data);
$conn->close();
?>
