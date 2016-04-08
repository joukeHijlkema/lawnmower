// wait for the svg to load
var mySVG = document.getElementById("backDrop");
var svgDoc;
mySVG.addEventListener("load",function() {
    svgDoc = mySVG.contentDocument;
    var date = new Date().toLocaleDateString("fr",{ weekday: 'long', year: 'numeric', month: 'long', day: 'numeric' });
    setDate(date);
}, false);

var myFloat = new Intl.NumberFormat("fr-FR",{maximumFractionDigits: 1 });

function setDate(date) {
    svgDoc.getElementById("myDateText").textContent=date;
    d3.json("Scripts/getData.php?what=actual",function(error, data) {
	data.forEach(function(d) {
	    svgDoc.getElementById("myTemp").textContent=temp(d.Temperature);
	    svgDoc.getElementById("myHumidity").textContent=hum(d.Humidity);
	    svgDoc.getElementById("myPressure").textContent=pres(d.Pressure);
	    svgDoc.getElementById("myWindspeed").textContent=windSpeed(d.WindSpeed);
	    svgDoc.getElementById("myWinddir").textContent=windDir(d.WindDirection);
	    svgDoc.getElementById("myRain").textContent=rain(d.Rain);
	    
	});
    });
}

function temp(str) {
    return myFloat.format(str)+" °C";
}
function hum(str) {
    return myFloat.format(str)+" %";
}
function pres(str) {
    return myFloat.format(Math.floor(parseInt(str)/100.0))+" mb";
}
function windSpeed(str) {
    return myFloat.format(str)+" m/s";
}
function windDir(str) {
    var dir = parseInt(str);
   
    if      (dir <= 200) {return "Nord";}
    else if (dir <= 350) {return "Ouest";}
    else if (dir <= 550) {return "Sud Est";}
    else if (dir <= 700) {return "Nord Ouest";}
    else if (dir <= 725) {return "Est";}
    else if (dir <= 900) {return "Nord Est";}
    else {return "SO";}
}
function rain(str) {
    return myFloat.format(parseInt(str))+" mm/24h";
}
