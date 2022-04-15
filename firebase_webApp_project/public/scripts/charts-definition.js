// Create the charts when the web page loads
window.addEventListener('load', onload);

function onload(event){
  chartT = createTemperatureChart();
  chartPh = createPhChart();
  chartTds = createTdsChart();
  chartHardness = createHardnessChart();
  chartSalanity = createSalanityChart();
  chartChlorinity = createChlorinityChart();
}

// Create Temperature Chart
function createTemperatureChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-temperature',
      type: 'spline' 
    },
    series: [
      {
        name: 'Temperature Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Temperature Celsius Degrees' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Ph Chart
function createPhChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-ph',
      type: 'spline' 
    },
    series: [
      {
        name: 'pH Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'pH Units (1 - 14)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Tds Chart
function createTdsChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-tds',
      type: 'spline' 
    },
    series: [
      {
        name: 'TDS Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Total Dissolved Salts (ppm)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Hardness Chart
function createHardnessChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-hardness',
      type: 'spline' 
    },
    series: [
      {
        name: 'Hardness Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Hardness (ppm)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Salanity Chart
function createSalanityChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-salanity',
      type: 'spline' 
    },
    series: [
      {
        name: 'Salanity Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Salanity (ppt)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}

// Create Chlorinity Chart
function createChlorinityChart() {
  var chart = new Highcharts.Chart({
    chart:{ 
      renderTo:'chart-chlorinity',
      type: 'spline' 
    },
    series: [
      {
        name: 'Chlorinity Data'
      }
    ],
    title: { 
      text: undefined
    },
    plotOptions: {
      line: { 
        animation: false,
        dataLabels: { 
          enabled: true 
        }
      }
    },
    xAxis: {
      type: 'datetime',
      dateTimeLabelFormats: { second: '%H:%M:%S' }
    },
    yAxis: {
      title: { 
        text: 'Chlorinity (ppt)' 
      }
    },
    credits: { 
      enabled: false 
    }
  });
  return chart;
}
