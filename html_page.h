const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Motor Control</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
      background: linear-gradient(to right, #1d3557, #457b9d);
      color: #fff;
      display: flex;
      flex-direction: column;
      align-items: center;
      justify-content: center;
      height: 100vh;
      overflow: hidden;
    }
    .container {
      display: flex;
      justify-content: space-between;
      align-items: center;
      width: 80%;
    }
    .column {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
    }
    .row {
      display: flex;
      justify-content: flex-end; /* Align buttons to the far right */
      align-items: center;
      width: 100%;
    }
    button {
      margin: 10px;
      padding: 15px 30px;
      font-size: 1rem;
      color: #fff;
      background: #007bff;
      border: none;
      border-radius: 5px;
      cursor: pointer;
      transition: background 0.3s ease;
      user-select: none;
    }
    button:hover {
      background: #0056b3;
    }
    .debug {
      margin-top: 20px;
      font-size: 1.2rem;
      color: #ffd700;
      user-select: none;
    }
    .fullscreen {
      position: absolute;
      top: 10px;
      right: 10px;
      background: #28a745;
      user-select: none;
    }
    .slider-container {
      width: 100%;
      margin: 20px;
      text-align: center;
    }
    .slider {
      width: 50%;
    }
  </style>
</head>
<body>
  <button class="fullscreen" onclick="toggleFullscreen()">Fullscreen</button>
  <h1>rc_UNIMAP</h1>
  <div class="container">
    <!-- Left-hand side: Forward and Reverse (Vertical) -->
    <div class="column">
      <button onmousedown="sendCommandOnPress('forward')" onmouseup="sendStopOnRelease()" 
              ontouchstart="sendCommandOnPress('forward')" ontouchend="sendStopOnRelease()" 
              oncontextmenu="return false;">Forward</button>
      <button onmousedown="sendCommandOnPress('reverse')" onmouseup="sendStopOnRelease()" 
              ontouchstart="sendCommandOnPress('reverse')" ontouchend="sendStopOnRelease()" 
              oncontextmenu="return false;">Reverse</button>
    </div>
    <!-- Right-hand side: Left and Right (Horizontal, Aligned to the Far Right) -->
    <div class="row">
      <button onmousedown="sendCommandOnPress('left')" onmouseup="sendStopOnRelease()" 
              ontouchstart="sendCommandOnPress('left')" ontouchend="sendStopOnRelease()" 
              oncontextmenu="return false;">Left</button>
      <button onmousedown="sendCommandOnPress('right')" onmouseup="sendStopOnRelease()" 
              ontouchstart="sendCommandOnPress('right')" ontouchend="sendStopOnRelease()" 
              oncontextmenu="return false;">Right</button>
    </div>
  </div>
  <!-- Slider for Speed Control -->
  <div class="slider-container">
    <label for="speedSlider">Speed: <span id="speedValue">128</span></label>
    <input type="range" id="speedSlider" class="slider" min="0" max="255" value="128" 
           oninput="updateSpeed(this.value)">
  </div>
  <div class="debug" id="debug">Press a button to see its function.</div>

  <script>
    // Send command when the button is pressed
    function sendCommandOnPress(command) {
      fetch('/control?cmd=' + command)
        .then(response => response.text())
        .then(data => {
          document.getElementById('debug').textContent = `Command Sent: ${data}`;
        })
        .catch(error => {
          document.getElementById('debug').textContent = `Error: ${error}`;
        });
    }

    // Send "stop" command when the button is released
    function sendStopOnRelease() {
      fetch('/control?cmd=stop')
        .then(response => response.text())
        .then(data => {
          document.getElementById('debug').textContent = `Command Sent: Stop`;
        })
        .catch(error => {
          document.getElementById('debug').textContent = `Error: ${error}`;
        });
    }

    // Update the speed in the backend when the slider value changes
    function updateSpeed(value) {
      document.getElementById('speedValue').textContent = value;
      fetch('/control?cmd=speed&value=' + value)
        .then(response => response.text())
        .then(data => {
          document.getElementById('debug').textContent = `Speed Set: ${data}`;
        })
        .catch(error => {
          document.getElementById('debug').textContent = `Error: ${error}`;
        });
    }

    // Toggle fullscreen mode
    function toggleFullscreen() {
      if (!document.fullscreenElement) {
        document.documentElement.requestFullscreen();
      } else {
        if (document.exitFullscreen) {
          document.exitFullscreen();
        }
      }
    }
  </script>
</body>
</html>
)rawliteral";
