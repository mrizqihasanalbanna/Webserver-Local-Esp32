const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, shrink-to-fit=no">
    <title>Kelompok 4</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>
    <script src="https://kit.fontawesome.com/2e3ce63ccb.js" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
    <link href="https://fonts.googleapis.com/css2?family=Quicksand:wght@500&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="assets/css/styles.css">
    <style>
        .custom-control-label {
            /*added for alignment with the switch */
            padding-top: 0.5rem;
            padding-left: 2rem;
            padding-bottom: 0.1rem;
        }

        .custom-switch .custom-control-label::before {
            left: -2.25rem;
            height: 1.5rem;
            width: 3.5rem;
            /* it was 1.75rem before. Sliding way is longer than before. */
            pointer-events: all;
            border-radius: 1rem;
        }

        .custom-switch .custom-control-label::after {
            top: calc(0.25rem + 2px);
            left: calc(-2.25rem + 2px);
            width: calc(1.5rem - 4px);
            /*it was calc(1rem - 4px) before. Oval is bigger than before. */
            height: calc(1.5rem - 4px);
            /* it was calc(1rem - 4px) before. Oval is bigger than before. */
            background-color: #adb5bd;
            border-radius: 2rem;
            /* it was 0.5rem before. Oval is bigger than before. */
            transition: background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-transform 0.15s ease-in-out;
            transition: transform 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out;
            transition: transform 0.15s ease-in-out, background-color 0.15s ease-in-out, border-color 0.15s ease-in-out, box-shadow 0.15s ease-in-out, -webkit-transform 0.15s ease-in-out;
        }
        @media (prefers-reduced-motion: reduce) {
            .custom-switch .custom-control-label::after {
                transition: none;
            }
        }

        .custom-switch .custom-control-input:checked ~ .custom-control-label::after {
            background-color: #fff;
            -webkit-transform: translateX(2rem);
            /* translateX(0.75rem); */
            transform: translateX(2rem);
            /* translateX(0.75rem); */
        }
    </style>
</head>

<body style="background-color: rgb(245,245,245);">
    <h1 class="display-4 text-center"
        style="font-size: 50px; color: rgb(101,101,101); font-family: 'Quicksand'; font-weight: 500; background-color: transparent; margin: 50px;">
        <strong>Dashboard</strong></h1>
    <div>
        <div class="container">
            <div class="row" style="background-color: transparent; justify-content: center;">
                <div class="col-md-5" style="background-color: transparent; margin-bottom: 25px;">
                    <div class="card" style="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
                        <div class="card-body">
                            <div class="row align-items-center no-gutters mb-3" style="background-color: transparent;">
                                <div class="col-auto mr-1" style="background-color: transparent;"><i class="far fa-lightbulb fa-2x text-gray-300"
                                    style="color: rgb(131,131,131);font-size: 30px;"></i></div>
                                <div class="col">
                                    <div class="text-uppercase text-primary text-xs mb-1"><span
                                            class="text-capitalize text-gray-300" style="color: rgb(131,131,131); font-size: 20px; font-family: 'Quicksand';">Lights</span>
                                    </div>
                                </div>
                            </div>
                            <div class="card" style="background: linear-gradient(to right,#5b86e5, #36d1dc); margin-bottom: 8px;">
                                <div class="card-body">
                                    <div class="row align-items-center no-gutters" style="background-color: transparent;">
                                        <div class="col-auto" style="background-color: transparent; padding-right: 35px;"><i class="far fa-lightbulb fa-2x"
                                            style="color: white;font-size: 60px;"></i></div>
                                        <div class="col mr-2">
                                            <div class="row" style="background-color: transparent; margin-top: 10px;">
                                                <div class="text-uppercase text-primary text-xs"><span
                                                    class="text-capitalize text-white" style="font-size: 20px; font-family: 'Quicksand';">LED 1</span>
                                                </div>
                                                <div class="col ml-5" style="text-align: end;">
                                                    <div class="custom-control custom-switch">
                                                        <input type="checkbox" class="custom-control-input" id="customSwitch"  onclick="functionSwitch()">
                                                        <label class="custom-control-label" for="customSwitch"></label>
                                                    </div>
                                                </div>
                                            </div>
                                            <div class="row" style="background-color: transparent;">
                                                <div class="text-uppercase text-xs"><span
                                                    class="text-capitalize text-white" style="font-size: 40px; font-family: 'Quicksand';" id="valueSwitch"></span>
                                                </div>
                                            </div>
                                        </div>
                                    </div>
                                </div>
                            </div><br>
                        </div>
                    </div>
                </div>
                <div class="col-md-4" style="justify-content: space-between;">
                    <div class="sub-row" style="margin-bottom: 25px;">
                        <div class="card" style="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
                            <div class="card-body">
                                <div class="row align-items-center no-gutters">
                                    <div class="col mr-2" style="background-color: transparent;">
                                        <div class="text-uppercase text-primary text-xs" style="background-color: transparent;"><span
                                                class="text-capitalize text-gray-300" style="color: rgb(131,131,131); font-size: 20px; font-family: 'Quicksand';">Time</span></div>
                                        <div class="text-dark font-weight-bold h5" style="margin: 0px; padding: 0px;"><span class="text-black-50"
                                                style="font-size: 40px;" id="value1"></span></div>
                                    </div>
                                    <div class="col-auto"><i class="fas fa-clock fa-2x text-gray-300"
                                            style="color: rgb(131,131,131);font-size: 40px;"></i></div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <div class="sub-row" style="margin-bottom: 25px;">
                        <div class="card" style="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
                            <div class="card-body">
                                <div class="row align-items-center no-gutters">
                                    <div class="col mr-2" style="background-color: transparent;">
                                        <div class="text-uppercase text-primary text-xs" style="background-color: transparent;"><span
                                                class="text-capitalize text-gray-300" style="color: rgb(131,131,131); font-size: 20px; font-family: 'Quicksand';">Data</span>
                                        </div>
                                        <div class="text-dark font-weight-bold h5" style="margin: 0px; padding: 0px;"><span class="text-black-50"
                                                style="font-size: 40px;" id="value3"></span></div>
                                    </div>
                                    <div class="col-auto"><i class="far fa-chart-bar fa-2x text-gray-300"
                                            style="color: rgb(131,131,131);font-size: 40px;"></i></div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div>
        <div class="container" style="margin-bottom: 25px;">
            <div class="row" style="justify-content: center; background-color: transparent;">
                <div class="col-md-5">
                    <div class="card" style="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
                        <div class="card-body text-center shadow-sm">
                            <h6 style="font-size: 20px; color: rgb(131,131,131); font-family: 'Quicksand';">Current Time</h6>
                            <button class="btn btn-info btn-sm" type="button" id="Button_set" onClick="get_flag_set()" style="font-size: 12px; height: 30px; width: 70px; margin-bottom: 10px;">Set Time</button>
                            <form class="set" action="/" method='POST'>
                                <input type="datetime-local" step="1" value="2020-10-20T19:30:02" style="height: 25px; font-size: 10px; width: 166px; margin-bottom: 10px;" name="Manual" id="Input">
                                <button class="btn btn-dark btn-sm" type="submit" value="Submit" id="Button_manual" style="height: 30px;font-size: 12px;">Manual</button>
                            </form>
                            <div class="row" style="justify-content: center;">
                                <div class="col-md-2" style="background-color: transparent;">
                                    <h5 style="font-size: 16px;height: 12px; color: rgb(131,131,131); font-family: 'Quicksand';">or</h5>
                                </div>
                                <div class="col-md-2 p-0" style="background-color: transparent;">
                                    <form form class="set" action="/" method='POST' >
                                        <button class="btn btn-dark btn-sm" type="submit" name="Auto" value="Auto" id="Button_auto" style="font-size: 12px;height: 30px;">Auto</button>
                                    </form>
                                </div>
                            </div>
                            
                        </div>
                    </div>
                </div>
                <div class="col-md-4" style="background-color: transparent;">
                    <div class="card" style="box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);">
                        <div class="card-body text-center">
                            <h1 style="font-size: 20px; color: rgb(131,131,131); font-family: 'Quicksand'; background-color: transparent;">Status</span></h1>
                            <h1 style="font-size: 12px; color: rgb(0,0,255); background-color: transparent; margin-top: 0px; margin-bottom: -5px;"> banyak data yang tampil dalam grafik:</h1>
                            <form class="set" style="background-color: transparent;">
                                <input type="number" value="0" min="1" max="120" id="banyak_data"
                                    style="height: 30px; font-size: 25px; width: 66px; margin: 15px;">
                            </form>
                            <div class="row" style="justify-content: space-evenly;">
                                <div class="col-md-2 p-0" style="background-color: transparent;">
                                    <button class="btn btn-success" button class="btn btn-success" type="submit" value="Submit" id="Button_start" onClick="get_flag_start()">Start</button>
                                </div>
                                <div class="col-md-2 p-0" style="background-color: transparent;">
                                    <button class="btn btn-danger" type="button" id="Button_stop" onClick="get_flag_stop()">Stop</button>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div>
        <div class="container">
            <div class="row">
                <div class="col-md-12 col-xl-12 offset-xl-0">
                    <div><canvas id="Chart" width="400" height="400"></canvas></div>
                </div>
            </div>
        </div>
    </div>  
    <footer style="font-size: 11px;" class="page-footer white pt-4">
        <div class="footer-copyright text-center py-3">© 2020 Copyright: Kelompok 4  - Teknik Komputer PENS</div>
    </footer>

    <script>
        var Current = [];
        var Current_max = 0;
        var timeStamp = [];
        var button_start = document.getElementById("Button_start");
        var button_stop = document.getElementById("Button_stop");
        var button_manual = document.getElementById("Button_manual");
        var button_auto = document.getElementById("Button_auto");
        var button_set = document.getElementById("Button_set");
        //awalan
        button_manual.disabled = true;
        button_auto.disabled = true;
        button_start.disabled = false;
        button_set.disabled = false;
        button_stop.disabled = true;
        //state awal
        var flag = "Set";
        var flag_button = "start";
        //counter
        var counter = 0;
        //banyak data yang tampil
        var banyak_data = 1;
        var last_banyak_data = 0;

        function functionSwitch() {
            var checkSwitch = document.getElementById("valueSwitch");
            if (checkSwitch.innerHTML === "OFF") {
                valueSwitch.innerHTML = "ON";
                flag_button = "Manual_ON";
            } else {
                valueSwitch.innerHTML = "OFF";
                flag_button = "Manual_OFF";
            }
        }

        function get_flag_start() {
            banyak_data = parseInt(document.getElementById("banyak_data").value);
            if (last_banyak_data > banyak_data) {
                Current = [];
                timeStamp = [];
            }
            if (banyak_data > 1 && banyak_data < 120) {
                button_manual.disabled = true;
                button_auto.disabled = true;
                button_start.disabled = true;
                button_set.disabled = true;
                button_stop.disabled = false;
                flag = "Start";
            }
            //document.getElementById("demo").innerHTML = flag;
        }

        function get_flag_stop() {
            button_manual.disabled = true;
            button_auto.disabled = true;
            button_start.disabled = false;
            button_set.disabled = false;
            button_stop.disabled = true;
            flag = "Stop";
            last_banyak_data = banyak_data;
            //document.getElementById("demo").innerHTML = data;
        }

        function get_flag_set() {
            button_manual.disabled = false;
            button_auto.disabled = false;
            button_start.disabled = true;
            button_stop.disabled = true;
            button_set.disabled = true;
            //status
            document.getElementById("Status").innerHTML = "Set Time";
//            document.getElementById("Status_tanggal").innerHTML = " ";
            flag = "Set";
        }
        function showGraph() {
            var ctx = document.getElementById("Chart").getContext('2d');
            var Chart2 = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: timeStamp, //Bottom Labeling
                    datasets: [{
                        label: "Current",
                        fill: false, //Try with true
                        backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                        borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
                        data: Current,
                    }],
                },
                options: {
                    animation: false,
                    title: {
                        display: true,
                        text: "Data Grafik"
                    },
                    maintainAspectRatio: false,
                    elements: {
                        line: {
                            tension: 0.5
                        }
                    },
                    scales: {
                        yAxes: [{
                            ticks: {
                                beginAtZero: false
                            }
                        }]
                    }
                }
            });

        }

        window.onload = function () {
            console.log(new Date().toLocaleTimeString());
        };

        setInterval(function () {
            getData();
        }, 1000); //1000 = 1 s

        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var time = new Date().toLocaleTimeString();
                    var txt = this.responseText;
                    var obj = JSON.parse(txt);
                    var Waktu = obj.Waktu;
                    Waktu = Waktu[0]+Waktu[1];
                    var jam = parseInt(Waktu);
                    if(jam == 3){
                      flag_button = "Start";
                    }
                    if(jam == 17){
                      flag_button = "Start";
                    }
                    if (flag == "Start") {
                        //search data Max
                        if (Current_max <= parseInt(obj.Data_potensio)) {
                            Current_max = obj.Data_potensio;
                        }
                        //memunculkan data sebanyak request
                        if (counter >= banyak_data) {
                            for (var i = 0; i < banyak_data; i++) {
                                if (i == banyak_data - 1) {
                                    Current[i] = obj.Data_potensio;
                                    timeStamp[i] = obj.Waktu;
                                } else {
                                    Current[i] = Current[i + 1];
                                    timeStamp[i] = timeStamp[i + 1];
                                }
                            }
                        } else {
                            counter++;
                            Current.push(obj.Data_potensio);
                            timeStamp.push(obj.Waktu);
                        }

                        //Update Graphs
                        showGraph();

                        //Update Data Table
                        var table1 = document.getElementById("value1");
//                      var table2 = document.getElementById("valueSwitch");
                        var table3 = document.getElementById("value3");
//                      var table4 = document.getElementById("value4");
                        table1.innerHTML = obj.Tanggal;
//                      table2.innerHTML = obj.Kondisi_lampu;
                        table3.innerHTML = obj.Data_potensio;
                        if(obj.Kondisi_lampu == "mati") document.getElementById("valueSwitch").innerHTML = "OFF";
                        else document.getElementById("valueSwitch").innerHTML = "ON";
                        var box = document.getElementById("customSwitch");
                        if (document.getElementById("valueSwitch").innerHTML == "OFF") {
                            box.checked = false;
                        } else {
                            box.checked = true;
                        }

                        //status
                        document.getElementById("Status").innerHTML = "Start";
//                      document.getElementById("Status_tanggal").innerHTML = obj.Tanggal;
//                      if(obj.Kondisi_lampu === "terang") document.getElementById("valueSwitch").innerHTML = "ON";
//                      else document.getElementById("valueSwitch").innerHTML = "OFF";
                    } else {
                      //Update Data Table
                        var table1 = document.getElementById("value1");
//                      var table2 = document.getElementById("valueSwitch");
                        var table3 = document.getElementById("value3");
//                      var table4 = document.getElementById("value4");
                        table1.innerHTML = obj.Tanggal;
//                      table2.innerHTML = obj.Kondisi_lampu;
                        table3.innerHTML = obj.Data_potensio;
                        if(obj.Kondisi_lampu == "mati") document.getElementById("valueSwitch").innerHTML = "OFF";
                        else document.getElementById("valueSwitch").innerHTML = "ON";
                        var box = document.getElementById("customSwitch");
                        if (document.getElementById("valueSwitch").innerHTML == "OFF") {
                            box.checked = false;
                        } else {
                            box.checked = true;
                        }

                        //status
                        document.getElementById("Status").innerHTML = "Stop";
//                      document.getElementById("Status_tanggal").innerHTML = obj.Tanggal;
                        //document.getElementById("value1").innerHTML = obj.Waktu;
//                      if(obj.Kondisi_lampu === "terang") document.getElementById("valueSwitch").innerHTML = "ON";
//                      else document.getElementById("valueSwitch").innerHTML = "OFF";
                        showGraph();
                    }
                }
            };
            if (flag_button  == "Start"){
              xhttp.open("GET", "Start", true);
              xhttp.send();
            }else if(flag_button  == "Manual_ON"){
              xhttp.open("GET", "Manual_ON", true);
              xhttp.send();
            }else if(flag_button  == "Manual_OFF"){
              xhttp.open("GET", "Manual_OFF", true);
              xhttp.send();
            }else{
              xhttp.open("GET", "Start", true);
              xhttp.send();
            }
        }
    </script>

</body>

</html>

)=====";
