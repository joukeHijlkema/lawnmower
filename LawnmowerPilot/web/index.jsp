<%-- 
    Document   : index
    Created on : Sep 2, 2015, 2:37:33 PM
    Author     : hylkema
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <link rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.7.4/leaflet.css" />
    <link rel="stylesheet" href="styles.css" type="text/css">
    <script src="http://cdn.leafletjs.com/leaflet-0.7.4/leaflet.js"></script>
    <title>Grasmaaier Page</title>
  </head>
  
    <div id="map"></div>
    <script>
      var map = L.map('map').setView([43.168741, 1.192087],18);
      L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', {
        attribution: '&copy; <a href="http://osm.org/copyright">OpenStreetMap</a> contributors'
      }).addTo(map);

      L.marker([43.168741, 1.192087]).addTo(map)
              .bindPopup('grasmaaier')
              .openPopup();
    </script>
  
</html>

