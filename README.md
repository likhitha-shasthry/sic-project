<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ResQHer - Women's Safety Emergency Alert System</title>

<style>
body{
    font-family: Arial, Helvetica, sans-serif;
    margin:0;
    padding:0;
    background:#f5f7fb;
    color:#333;
}

header{
    background:#6c63ff;
    color:white;
    padding:30px;
    text-align:center;
}

section{
    padding:40px 80px;
}

h2{
    color:#6c63ff;
}

.card{
    background:white;
    padding:20px;
    margin:15px 0;
    border-radius:8px;
    box-shadow:0 2px 6px rgba(0,0,0,0.1);
}

.tech-list{
    display:grid;
    grid-template-columns:repeat(auto-fit,minmax(200px,1fr));
    gap:15px;
}

footer{
    text-align:center;
    padding:20px;
    background:#222;
    color:white;
}
</style>
</head>

<body>

<header>
<h1>ResQHer</h1>
<p>IoT-Based Women's Safety Emergency Alert System using ESP32</p>
</header>

<section>
<h2>Abstract</h2>
<div class="card">
<p>
Women's safety remains a critical concern in both urban and rural environments. 
In emergency situations, individuals often lack a quick and reliable way to 
send alerts and share their location with trusted contacts or authorities. 
ResQHer is an IoT-based wearable emergency alert system built using ESP32 that 
allows users to trigger an SOS alert instantly through a simple double-tap 
gesture on a touch sensor.
</p>
</div>
</section>

<section>
<h2>Problem Statement</h2>
<div class="card">
<ul>
<li>Emergency situations leave little time to unlock phones or dial numbers.</li>
<li>Many existing safety apps involve multiple steps to trigger alerts.</li>
<li>Users need a fast and simple emergency activation system.</li>
<li>Location tracking is necessary for quick rescue response.</li>
</ul>
</div>
</section>

<section>
<h2>Project Objectives</h2>
<div class="card">
<ul>
<li>Design a compact wearable emergency alert system.</li>
<li>Implement double-tap detection using a capacitive touch sensor.</li>
<li>Use ESP32 microcontroller for processing and connectivity.</li>
<li>Generate latitude and longitude coordinates.</li>
<li>Store emergency data in Google Sheets for monitoring.</li>
</ul>
</div>
</section>

<section>
<h2>System Architecture</h2>
<div class="card">
<ol>
<li><b>Wearable Device Layer</b> – Capacitive touch sensor detects user activation.</li>
<li><b>ESP32 Processing Unit</b> – Processes the double-tap trigger and generates coordinates.</li>
<li><b>Cloud Storage</b> – Emergency alerts and location data are stored in Google Sheets.</li>
</ol>
</div>
</section>

<section>
<h2>Technologies Used</h2>

<div class="tech-list">

<div class="card">
<h3>Hardware</h3>
<ul>
<li>ESP32-C6 Microcontroller</li>
<li>Capacitive Touch Sensor</li>
<li>Breadboard and Jumper Wires</li>
<li>Power Supply</li>
</ul>
</div>

<div class="card">
<h3>Software</h3>
<ul>
<li>Arduino IDE</li>
<li>C Programming</li>
<li>Google Sheets API</li>
</ul>
</div>

</div>
</section>

<section>
<h2>Implementation</h2>
<div class="card">
<ul>
<li>Touch sensor detects a double-tap gesture.</li>
<li>ESP32 processes the input and generates coordinates.</li>
<li>Event logs are displayed in the Arduino Serial Monitor.</li>
<li>Data is stored in Google Sheets for remote tracking.</li>
</ul>
</div>
</section>

<section>
<h2>Results</h2>
<div class="card">
<p>The prototype successfully demonstrates the emergency alert functionality:</p>
<ul>
<li>Touch sensor activates SOS alert.</li>
<li>Coordinates are generated.</li>
<li>Logs are displayed in Serial Monitor.</li>
<li>Data is stored in Google Sheets.</li>
</ul>

<p><b>Example Log:</b></p>

<pre>
[14:02:15] SOS ACTIVATED
[14:02:16] Coordinates: 12.9734, 77.5867
[14:02:17] Data saved to Google Sheets
</pre>

</div>
</section>

<section>
<h2>Challenges Faced</h2>
<div class="card">
<ul>
<li>Implementing reliable double-tap gesture detection.</li>
<li>Generating realistic latitude and longitude values.</li>
<li>Configuring Google Sheets API integration.</li>
<li>Debugging real-time serial communication.</li>
</ul>
</div>
</section>

<section>
<h2>Future Improvements</h2>
<div class="card">
<ul>
<li>Integrate real GPS module instead of simulated coordinates.</li>
<li>Add GSM module for sending SMS alerts.</li>
<li>Develop a mobile application for monitoring alerts.</li>
<li>Miniaturize the device for wearable deployment.</li>
</ul>
</div>
</section>

<footer>
<p>© 2026 ResQHer Project | IoT Women's Safety System</p>
</footer>

</body>
</html>