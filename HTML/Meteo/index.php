<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>Meteo</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <meta name="PageTitle" content="Html" />
    <script type='text/javascript' src="Scripts/d3.min.js" charset="utf-8"></script>
    <script type='text/javascript' src="Scripts/Meteo.js" charset="utf-8"></script>
    <link href='Styles/Styles.css' rel='stylesheet' type='text/css'>
  </head>
  <body>
      <svg id="temp"></svg>
      <svg id="pressure"></svg>
      <svg id="humidity"></svg>
      <script type='text/javascript'>drawCombined("#temp",'today','Temperature','Température',-10,40);</script>
      <script type='text/javascript'>drawCombined("#pressure",'today','Pressure','Pression',90000,110000);</script>
      <script type='text/javascript'>drawCombined("#humidity",'today','humidity','humidité',30,90);</script>
  </body>
</html>

