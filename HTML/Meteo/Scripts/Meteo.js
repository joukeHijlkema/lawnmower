var margin = {top: 40, right: 20, bottom: 30, left: 50},
    width  = 900 - margin.left - margin.right,
    height = 250 - margin.top  - margin.bottom;

function parseDate(date) {
    return d3.time.format("%Y-%m-%d %H:%M:%S").parse(date);
}

function drawLine(container,date,col,ymin,ymax) {

    var x = d3.time.scale().range([0, width]).nice(d3.time.hour);
    var y = d3.scale.linear().range([height, 0]);

    var xAxisDay   = d3.svg.axis().scale(x).orient("top").ticks(12).tickFormat(d3.time.format("%H:%M"));
    var yAxis      = d3.svg.axis().scale(y).orient("left").ticks(10);

    var valueline = d3.svg.line()
	.x(function(d) { return x(d.Time); })
	.y(function(d) { return y(d.Value); });

    var svg = d3.select(container)
	.attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
	.append("g")
	.attr("class","lineGraph")
	.attr("id",container.substring(1)+"_lineGraph")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    var start = d3.time.format("%Y-%m-%d").parse(date);
    var end   = d3.time.day.offset(start, 1);
    var cmd   = 'Scripts/getData.php?period=day&type=raw'+
	'&start='+d3.time.format("%Y-%m-%d 00:00:00")(start)+
	'&end='  +d3.time.format("%Y-%m-%d 00:00:00")(end)+
	'&col='  +col;
    
    d3.json(cmd, function(error, data) {
	data.forEach(function(d) {
	    d.Time  = parseDate(d.Time);
	    d.Value = d.Value;
	});
	
	// Scale the range of the data
	x.domain([start,end]);
	y.domain([ymin,ymax]);

	svg.append("path")      // Add the valueline path.
            .attr("class", "line")
            .attr("d", valueline(data));

	svg.append("g")         // Add the X Axis for days ot top
            .attr("class", "x axis line")
            .attr("transform", "translate(0,0)")
            .call(xAxisDay);
	
	svg.append("g")         // Add the Y Axis
            .attr("class", "y axis line")
            .call(yAxis);

    });
}

function drawBar(container,date,col,ymin,ymax) {

    var x = d3.time.scale().range([0, width]).nice(d3.time.hour);
    var y = d3.scale.linear().range([height, 0]);

    var xAxis = d3.svg.axis().scale(x).orient("bottom").ticks(10).tickFormat(d3.time.format("%d"));
    var yAxis = d3.svg.axis().scale(y).orient("right").ticks(10);

    var svg = d3.select(container)
	.attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
	.append("g")
	.attr("class","barGraph")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

    var start = d3.time.month.floor(d3.time.format("%Y-%m-%d").parse(date));
    var end   = d3.time.day.offset(d3.time.month.offset(start,1),-1);
    var cmd   = 'Scripts/getData.php?period=month&type=avg'+
	'&start='+d3.time.format("%Y-%m-%d 00:00:00")(start)+
	'&end='  +d3.time.format("%Y-%m-%d 00:00:00")(end)+
	'&col='  +col;
    // alert(cmd);
    var nbDays   = parseInt(d3.time.format("%d")(end))-parseInt(d3.time.format("%d")(start))+1;
    var barWidth = 0.9*(width/nbDays)-2;
    
    d3.json(cmd, function(error, data) {
	data.forEach(function(d) {
	    d.Time  = parseDate(d.Time);
	    d.Value = d.Value;
	});
	
	// Scale the range of the data
	x.domain([start,end]);
	y.domain([ymin,ymax]);

	svg.append("g")         // Add the X Axis for days ot top
	    .attr("class", "x axis")
            .attr("transform", "translate(0," + height + ")")
            .call(xAxis);
	
	svg.append("g")         // Add the Y Axis
            .attr("class", "y axis")
	    .attr("transform", "translate("+width+",0)")
            .call(yAxis);

	svg.selectAll(".bar")
	    .attr("id","barGraph")
	    .data(data)
	    .enter().append("rect")
	    .attr("class", "bar")
	    .attr("x", function(d) {return x(d3.time.day.floor(d.Time)); })
	    .attr("width", barWidth)
	    .attr("y", function(d) { return y(d.Value); })
	    .attr("height", function(d) { return height - y(d.Value); })
	    .on('click', function(d){
		var target = container+"_lineGraph";
		d3.select(target).remove();
		drawLine(container,d3.time.format("%Y-%m-%d")(d.Time),col,ymin,ymax);});;

    });
}

function drawCombined(container,date,col,title,ymin,ymax) {
    if (date=='today') {
	date = d3.time.format("%Y-%m-%d")(new Date());
    }
    var svg = d3.select(container)
    	.append("text")
    	.attr("class","title")
    	.attr("x","0")
    	.attr("y","1em")
    	.text(title);
    
    drawLine(container,date,col,ymin,ymax);
    drawBar(container,date,col,ymin,ymax);
}

/* Ideen :
- maak min max en avg line en bar in alle 3
*/
