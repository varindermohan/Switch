function enselect(){
  if(document.getElementById("mqttenablelocal").value=="No")
  {document.getElementById("mqttenableremote").value="Yes";}
  else{document.getElementById("mqttenableremote").value="No";}
  }
function enselect1(){
  if(document.getElementById("mqttenableremote").value=="No")
  {document.getElementById("mqttenablelocal").value="Yes";}
  else{document.getElementById("mqttenablelocal").value="No";}
 }
function updateportsettings() {
  var myTab = document.getElementById('myTable4');
  var iRow = myTab.rows.length;
  var json = "";
  console.log(iRow);
  i = 1;
  var objCells = myTab.rows.item(i).cells;
  if (objCells.item(0).innerHTML != "&nbsp;") {
    json += "{\"port_no\":\"";
    json += objCells.item(0).innerHTML;
    json += "\",\"gpio\":\"";
    json += objCells.item(1).innerHTML;
    json += "\",\"enable_status\":\"";
    json += objCells.item(2).innerHTML;
    json += "\",\"control\":\"";
    json += objCells.item(3).innerHTML;
    json += "\",\"server\":\"";
    json += objCells.item(4).innerHTML;
    json += "\",\"type_of_pin\":\"";
    json += objCells.item(5).innerHTML;
    json += "\",\"speed\":\"";
    json += objCells.item(6).innerHTML;
    json += "\",\"connected_device\":\"";
    json += objCells.item(7).innerHTML;
    json += "\",\"area\":\"";
    json += objCells.item(8).innerHTML;
    json += "\",\"timer_type\":\"";
    json += objCells.item(9).innerHTML;
    json += "\",\"on_time\":\"";
    json += objCells.item(10).innerHTML;
    json += "\",\"off_time_duration\":\"";
    json += objCells.item(11).innerHTML;
    json += "\",\"days\":\"";
    json += objCells.item(12).innerHTML;
    json += "\",\"mqtt_topic\":\"";
    json += objCells.item(13).innerHTML;
    json += "\"}"
    console.log(json);
    var url = "/updateportdata?data1=" + json + "&data2=" + objCells.item(0).innerHTML;
    window.open(url, "_self");
  }
}
function savegenset() {
  serialspeed = document.getElementById('serialspeed').value;
  adminpassword = document.getElementById('adminpassword').value;
  sitename = document.getElementById('sitename').value;
  userpassword = document.getElementById('userpassword').value;
  hotspotssidname = document.getElementById('hotspotssidname').value;
  hotspotpassword = document.getElementById('hotspotpassword').value;
  var json = "";
  if (serialspeed.trim() == "" || adminpassword.trim() == "" || sitename.trim() == "" || userpassword.trim() == "") {
    alert("Blank Data not allowed");
  }
  else {
    json = "\"site_name\":\"";
    json += sitename;
    json += "\",\"serial_speed\":\"";
    json += serialspeed;
    json += "\",\"admin_password\":\"";
    json += adminpassword;
    json += "\",\"user_password\":\"";
    json += userpassword;
    json += "\",\"hotspot_name\":\"";
    json += hotspotssidname;
    json += "\",\"hotspot_password\":\"";
    json += hotspotpassword;
    json += "\"}";
    console.log(json);
    var url = "/updategenset?data1=" + json;
    window.open(url, "_self");
  }
}
function rebootesp() {
  var url = "/rebootsystem";
  window.open(url, "_self");
}
function resetgenset() {
  document.getElementById("sitename").value = "";
  document.getElementById("adminpassword").value = "";
  document.getElementById("userpassword").value = "";
}

function delwifiuname() {
  var ssid = prompt("Please Enter SSID Name : ");
  var objTable = document.getElementById("myTable5")
  var iRow = objTable.rows.length;
  var counter = 0;
  console.log(iRow);
  if (objTable.rows.length > 1) {
    for (var i = 0; i < objTable.rows.length; i++) {
      var chk = objTable.rows[i].cells[0].innerHTML;
      if (chk == ssid) {
        objTable.deleteRow(i);
        console.log(chk + " " + ssid);
        iRow--;
        i--;
        counter = counter + 1;
      }
    }
  }
}
function updatewifissid() {
  var myTab = document.getElementById('myTable5');
  var iRow = myTab.rows.length;
  var json = "";
  console.log(iRow);
  json += "{ \"stored_ssid\":[";
  if (iRow > 1) {
    for (i = 1; i < myTab.rows.length; i++) {
      json += "{\"ssid\":\"";
      var objCells = myTab.rows.item(i).cells;
      json += objCells.item(0).innerHTML;
      json += "\",\"password\":\"";
      json += objCells.item(1).innerHTML;
      json += "\",\"priority\":\"";
      json += objCells.item(2).innerHTML;
      json += "\"}"
      if (i + 1 < iRow) { json += "," }
    }
    json += "]}";
    console.log(json);
    var url = "/updatessidfile?data1=" + json;
    window.open(url, "_self");
  }
}
function savemqttdata() {
  var rd1 = document.getElementById("Auth");
  var rd2 = document.getElementById("Auth1");
  var rd3 = document.getElementById("Auth2");
  var rd4 = document.getElementById("Auth3");
  if (rd1.checked == true) {f = "0";}
  if (rd2.checked == true) {f = "1";}
  if (rd3.checked == true) {f1 = "0";}
  if (rd4.checked == true) {f1 = "1";}
  if (f=="0"){
    document.getElementById('mqttusernamelocal').value=" ";
    document.getElementById('mqttpasswordlocal').value=" ";
  }
  if (f1=="0"){
    document.getElementById('mqttusernameremote').value=" ";
    document.getElementById('mqttpasswordremote').value=" ";
  }
  a = document.getElementById('mqttenablelocal').value;
  b = document.getElementById('mqtturllocal').value;
  c = document.getElementById('mqttportnumlocal').value;
  d = document.getElementById('mqttusernamelocal').value;
  e = document.getElementById('mqttpasswordlocal').value;
  a1 = document.getElementById('mqttenableremote').value;
  b1 = document.getElementById('mqtturlremote').value;
  c1 = document.getElementById('mqttportnumremote').value;
  d1 = document.getElementById('mqttusernameremote').value;
  e1 = document.getElementById('mqttpasswordremote').value;
  if (a.trim() == "" || b.trim() == "" || a1.trim() == "" || b1.trim() == "") {
    alert("Blank Data not allowed");
  }
  else if (c.trim() == "" || c1.trim() == "") {
    alert("Invalid Port Number");
  }
  else {
    json = "{\"lms_enabled\":\"";
    json += document.getElementById('mqttenablelocal').value;
    json += "\",\"lms_url\":\"";
    json += (document.getElementById('mqtturllocal').value).trim();
    json += "\",\"lms_port\":\"";
    json += (document.getElementById('mqttportnumlocal').value).trim();
    json += "\",\"lms_auth\":\"";
    json += f;
    json += "\",\"lms_user_name\":\"";
    json += (document.getElementById('mqttusernamelocal').value).trim();
    json += "\",\"lms_password\":\"";
    json += (document.getElementById('mqttpasswordlocal').value).trim();
    json += "\",\"rms_enabled\":\"";
    json += document.getElementById('mqttenableremote').value;
    json += "\",\"rms_url\":\"";
    json += (document.getElementById('mqtturlremote').value).trim();
    json += "\",\"rms_port\":\"";
    json += (document.getElementById('mqttportnumremote').value).trim();
    json += "\",\"rms_auth\":\"";
    json += f1;
    json += "\",\"rms_user_name\":\"";
    json += (document.getElementById('mqttusernameremote').value).trim();
    json += "\",\"rms_password\":\"";
    json += (document.getElementById('mqttpasswordremote').value).trim();
    json += "\"}";
    var url = "/updatemqtt?data1=" + json;
    window.open(url, "_self");
  }
}

function resetmqttdata() {
  document.getElementById('mqttenablelocal').value = "";
  document.getElementById('mqtturllocal').value = "";
  document.getElementById('mqttportnumlocal').value = "";
  document.getElementById('mqttusernamelocal').value = "";
  document.getElementById('mqttpasswordlocal').value = "";
  document.getElementById('mqttenableremote').value = "";
  document.getElementById('mqtturlremote').value = "";
  document.getElementById('mqttportnumremote').value = "";
  document.getElementById('mqttusernameremote').value = "";
  document.getElementById('mqttpasswordremote').value = "";
}
function saveserverdata() {
  a = document.getElementById('serverenablelocal').value;
  b = document.getElementById('serverurllocal').value;
  c = document.getElementById('serveraccesstokenlocal').value;
  d = document.getElementById('serverusernamelocal').value;
  e = document.getElementById('serverpasswordlocal').value;
  a1 = document.getElementById('serverenableremote').value;
  b1 = document.getElementById('serverurlremote').value;
  c1 = document.getElementById('serveraccesstokenremote').value;
  d1 = document.getElementById('serverusernameremote').value;
  e1 = document.getElementById('serverpasswordremote').value;
  if (a.trim() == "" || b.trim() == "" || d.trim() == "" || e.trim() == "" || a1.trim() == "" || b1.trim() == "" || d1.trim() == "" || e1.trim() == "") {
    alert("Blank Data not allowed");
  }
  else if (c.trim() == "" || c1.trim() == "") {
    alert("Blank Data not allowed");
  }
  else {
    json = "{\"local_server\":{\"enabled\":\"";
    json += document.getElementById('serverenablelocal').value;
    json += "\",\"url\":\"";
    json += document.getElementById('serverurllocal').value;
    json += "\",\"access_token\":\"";
    json += document.getElementById('serveraccesstokenlocal').value;
    json += "\",\"user_name\":\"";
    json += document.getElementById('serverusernamelocal').value;
    json += "\",\"password\":\"";
    json += document.getElementById('serverpasswordlocal').value;
    json += "\"},\"remote_server\":{\"enabled\":\"";
    json += document.getElementById('serverenableremote').value;
    json += "\",\"url\":\"";
    json += document.getElementById('serverurlremote').value;
    json += "\",\"access_token\":\"";
    json += document.getElementById('serveraccesstokenremote').value;
    json += "\",\"user_name\":\"";
    json += document.getElementById('serverusernameremote').value;
    json += "\",\"password\":\"";
    json += document.getElementById('serverpasswordremote').value;
    json += "\"}}";
    console.log(json);
    var url = "/updateserver?data1=" + json;
    window.open(url, "_self");
  }
}
function resetserverata() {
  document.getElementById('serverenablelocal').value = "";
  document.getElementById('serverurllocal').value = "";
  document.getElementById('serveraccesstokenlocal').value = "";
  document.getElementById('serverusernamelocal').value = "";
  document.getElementById('serverpasswordlocal').value = "";
  document.getElementById('serverenableremote').value = "";
  document.getElementById('serverurlremote').value = "";
  document.getElementById('serveraccesstokenremote').value = "";
  document.getElementById('serverusernameremote').value = "";
  document.getElementById('serverpasswordremote').value = "";
}
function addrow() {
  var rd1 = document.getElementById("detectedssid1");
  var rd2 = document.getElementById("customssid1");
  if (rd1.checked == true) {
    if (document.getElementById("detectedssid").value == "") {
      alert("Blank SSID");
      return false;
    }
    addrow1(document.getElementById("detectedssid").value, document.getElementById("ssidPassword").value, document.getElementById("priority").value);
  }
  else if (rd2.checked == true) {
    if (document.getElementById("customssid").value == "") {
      alert("Blank SSID");
      return false;
    }
    addrow1(document.getElementById("customssid").value, document.getElementById("ssidPassword").value, document.getElementById("priority").value);
  }
}
function addrow1(ssid, password, priority) {
  var table = document.getElementById("myTable5");
  var currentIndex = myTable5.rows.length;
  var row = table.insertRow(currentIndex);
  var cell1 = row.insertCell(0);
  var cell2 = row.insertCell(1);
  var cell3 = row.insertCell(2);
  cell1.innerHTML = ssid;
  cell2.innerHTML = password;
  cell3.innerHTML = priority;
}
function selectwifi() {
  var objTable = document.getElementById("myTable1")
  var x = document.getElementById("detectedssid");
  var n = 1;
  while (n <= x.length) {
    console.log(n + "   " + x.length)
    x.remove(0);
  }
  var option = document.createElement("option");
  var iRow = objTable.rows.length;
  for (var i = 1; i < objTable.rows.length; i++) {
    var chk = objTable.rows[i].cells[0].innerHTML;
    var option = document.createElement("option");
    console.log(chk);
    option.text = chk;
    x.add(option);
  }
}
function chgtopicdata() {
  var chip_site_id = document.getElementById("chip_site_id").innerText;
  var house_name = document.getElementById("housename").value;
  var portnum = document.getElementById("portno").value;
  var gpionum = document.getElementById("gpionumber").value;
  var gpioenable = document.getElementById("gpioenable").value;
  var devicecontrol = document.getElementById("devicecontrol").value;
  var remotecontrol = document.getElementById("remotecontrol").value;
  var gpiotype = document.getElementById("gpiotype").value;
  var speed = document.getElementById("speed").value;
  var Itemname = document.getElementById("Itemname").value;
  var numberitem = document.getElementById("numberitem").value;
  var area = document.getElementById("area").value;
  var numberarea = document.getElementById("numberarea").value;
  var timer = document.getElementById("timer").value;
  var ontime = document.getElementById("ontime").value;
  var offtime = document.getElementById("offtime").value;
  var dayonce = document.getElementById("dayonce").checked;
  var dayall = document.getElementById("dayall").checked;
  var days = 0;
  var table1 = document.getElementById("myTable4");
  table1.rows[1].cells[0].innerHTML = portnum;
  table1.rows[1].cells[1].innerHTML = gpionum;
  table1.rows[1].cells[2].innerHTML = gpioenable;
  table1.rows[1].cells[3].innerHTML = devicecontrol;
  table1.rows[1].cells[4].innerHTML = remotecontrol;

  table1.rows[1].cells[5].innerHTML = gpiotype;
  if (gpiotype=="Sensor")
  {
    speed="0";
    timer="OFF";
  }
  console.log(gpiotype);
  table1.rows[1].cells[6].innerHTML = speed;
  table1.rows[1].cells[7].innerHTML = Itemname + "-" + numberitem;
  table1.rows[1].cells[8].innerHTML = area + "-" + numberarea;
  table1.rows[1].cells[9].innerHTML = timer;
  table1.rows[1].cells[10].innerHTML = ontime;
  table1.rows[1].cells[11].innerHTML = offtime;
  

  var x = chip_site_id + "/" + house_name + "/" + area + "/" + numberarea + "/" + Itemname + "/" + numberitem;
  if (timer == "On/Off Time") 
  {
    if (dayonce == true) {days = "1";}
    else if (dayall == true) {days = "7";}
  } else if (timer == "OFF" || timer == "OnTime-Duration") {days = "0";}
  table1.rows[1].cells[12].innerHTML = days;
  table1.rows[1].cells[13].innerHTML = x;
}

function readmacaddress() {
  document.getElementById("Uniquesiteid").innerText = "site_address";
}
function fn1() {
  var rd1 = document.getElementById("detectedssid1");
  var rd2 = document.getElementById("customssid1");
  if (rd1.checked == true) {
    document.getElementById("detectedssid").style.visibility = "visible";
    document.getElementById("customssid").style.visibility = "hidden";
}else if (rd2.checked == true) {
    document.getElementById("detectedssid").style.visibility = "hidden";
    document.getElementById("customssid").style.visibility = "visible";
  }
}
function selauth1() {
    if (document.getElementById("Auth2").checked) {
    console.log("First Radio Button selected");
    document.getElementById("lblusna1").style.visibility = "hidden";
    document.getElementById("mqttusernameremote").style.visibility = "hidden";
    document.getElementById("lblpass1").style.visibility = "hidden";
    document.getElementById("mqttpasswordremote").style.visibility = "hidden";
  }
  else {
    console.log("Second Radio Button selected");
    document.getElementById("lblusna1").style.visibility = "visible";
    document.getElementById("mqttusernameremote").style.visibility = "visible";
    document.getElementById("lblpass1").style.visibility = "visible";
    document.getElementById("mqttpasswordremote").style.visibility = "visible";
  }
}
function selauth() {
  if (document.getElementById("Auth").checked) {
    console.log("First Radio Button selected");
    document.getElementById("lblusna").style.visibility = "hidden";
    document.getElementById("mqttusernamelocal").style.visibility = "hidden";
    document.getElementById("lblpass").style.visibility = "hidden";
    document.getElementById("mqttpasswordlocal").style.visibility = "hidden";
  }  else {
    console.log("second Radio Button selected");
    document.getElementById("lblusna").style.visibility = "visible";
    document.getElementById("mqttusernamelocal").style.visibility = "visible";
    document.getElementById("lblpass").style.visibility = "visible";
    document.getElementById("mqttpasswordlocal").style.visibility = "visible";
  }
}
  function fn2() {
    var rd1 = document.getElementById("addconfig");
    var rd2 = document.getElementById("delconfig");
    if (rd1.checked == true) {
      document.getElementById("gpioenable").style.visibility = "visible";
      document.getElementById("localsiteid").style.visibility = "visible";
      document.getElementById("housename").style.visibility = "visible";
      document.getElementById("area").style.visibility = "visible";
      document.getElementById("numberarea").style.visibility = "visible";
      document.getElementById("Itemname").style.visibility = "visible";
      document.getElementById("numberitem").style.visibility = "visible";
      document.getElementById("devicecontrol").style.visibility = "visible";
      document.getElementById("remotecontrol").style.visibility = "visible";
      document.getElementById("gpionumber").style.visibility = "visible";
      document.getElementById("gpiotype").style.visibility = "visible";
      document.getElementById("speed").style.visibility = "visible";
      document.getElementById("timer").style.visibility = "visible";
      document.getElementById("ontime").style.visibility = "visible";
      document.getElementById("offtime").style.visibility = "visible";
      document.getElementById("days").style.visibility = "visible";
      selecttimertype();
      butsel();
    }
    else if (rd2.checked == true) {
      document.getElementById("gpioenable").style.visibility = "hidden";
      document.getElementById("localsiteid").style.visibility = "hidden";
      document.getElementById("housename").style.visibility = "hidden";
      document.getElementById("area").style.visibility = "hidden";
      document.getElementById("numberarea").style.visibility = "hidden";
      document.getElementById("Itemname").style.visibility = "hidden";
      document.getElementById("numberitem").style.visibility = "hidden";
      document.getElementById("devicecontrol").style.visibility = "hidden";
      document.getElementById("remotecontrol").style.visibility = "hidden";
      document.getElementById("gpionumber").style.visibility = "hidden";
      document.getElementById("gpiotype").style.visibility = "hidden";
      document.getElementById("speed").style.visibility = "hidden";
      document.getElementById("timer").style.visibility = "hidden";
      document.getElementById("ontime").style.visibility = "hidden";
      document.getElementById("offtime").style.visibility = "hidden";
      document.getElementById("days").style.visibility = "hidden";
    }
  }
  function dailytimer() {
    if (document.getElementById("dayall").checked == true) {
      document.getElementById("dayonce").checked = false;
    }
    else if (document.getElementById("dayall").checked == false) {
      document.getElementById("dayonce").checked = true;
    }
  }
  function butsel() {
    if (document.getElementById("gpiotype").value == "Switch") {
      document.getElementById("speed").value = "5";
    }
    if (document.getElementById("gpiotype").value == "Sensor") {
      portinputitemlist();
      sortItemname();
      document.getElementById("speed").style.visibility = "hidden";
      document.getElementById("timer").style.visibility = "hidden";
    }
    else{
      portoutputitemlist();
      document.getElementById("speed").style.visibility = "visible";
      document.getElementById("timer").style.visibility = "visible";
      sortItemname();
    }
  }

  function devcontrol() {
    if (document.getElementById("devicecontrol").value == "Direct") {
      document.getElementById("remotecontrol").value = "None";
    }
  }
  function selectser1() {
    if (document.getElementById("remotecontrol").value != "None") {
      document.getElementById("devicecontrol").value = "Server"
    }
    else {
      document.getElementById("devicecontrol").value = "Direct"
    }
  }
  function selspeed1() {
    if (document.getElementById("speed").value != "5") {
      document.getElementById("gpiotype").value = "Dimmer"
    }
  }
  function dailytimer2() {
    if (document.getElementById("dayonce").checked == true) {
      document.getElementById("dayall").checked = false;
    }
    else {
      document.getElementById("dayall").checked = true;
    }
  }
  function selecttimertype() {
    if (document.getElementById("timer").value == "OFF") {
      //document.getElementById("lblontime").style.visibility = "hidden";
      document.getElementById("ontime").style.visibility = "hidden";
      // document.getElementById("lblofftime").style.visibility = "hidden";
      document.getElementById("offtime").style.visibility = "hidden";
      document.getElementById("days").style.visibility = "hidden";
      document.getElementById("dayonce").checked = false;
      document.getElementById("dayall").checked = false;
      document.getElementById("offtime").type = "text";
      document.getElementById("ontime").type = "text";
      document.getElementById("ontime").value = "None";
      document.getElementById("offtime").value = "None";
    }
    else if (document.getElementById("timer").value == "On/Off Time") {
      // document.getElementById("lblontime").style.visibility = "visible";
      document.getElementById("ontime").style.visibility = "visible";
      // document.getElementById("lblofftime").style.visibility = "visible";
      document.getElementById("offtime").style.visibility = "visible";
      document.getElementById("days").style.visibility = "visible";
      document.getElementById("dayonce").checked = true;
      document.getElementById("dayall").checked = false;
      // document.getElementById("lblofftime").innerHTML="&rarr; OFF Time";
      document.getElementById("offtime").placeholder = "OFF TIME";
      document.getElementById("ontime").placeholder = "ON Time";
      document.getElementById("offtime").type = "time";
      document.getElementById("ontime").type = "time";
      document.getElementById("offtime").value = "";
      document.getElementById("ontime").value = "";
    }
    else if (document.getElementById("timer").value == "OnTime-Duration") {
      var date = new Date();
      var hh = date.getHours();
      var mm = date.getMinutes();
      // document.getElementById("lblontime").style.visibility = "visible";
      document.getElementById("ontime").style.visibility = "visible";
      // document.getElementById("lblofftime").style.visibility = "visible";
      document.getElementById("offtime").style.visibility = "visible";
      document.getElementById("days").style.visibility = "hidden";
      // document.getElementById("lblofftime").innerHTML="&rarr; Duration";
      document.getElementById("offtime").placeholder = "Duration in seconds";
      document.getElementById("ontime").placeholder = "Current Time";
      document.getElementById("ontime").value = "";
      document.getElementById("offtime").value = "";
      document.getElementById("dayonce").checked = false;
      document.getElementById("dayall").checked = false;
      document.getElementById("offtime").type = "text";
      document.getElementById("ontime").type = "time";
      document.getElementById("ontime").value = hh + ":" + mm;
      document.getElementById("offtime").value = "30";
    }
  }
  function validate() {
    var username = document.getElementById("loginusername");
    var password = document.getElementById("loginpassword");
    var password1 = document.getElementById("loginpassword1");
    if (username.value.trim() == "") {
      alert("Blank Username");
      username.style.border = "Solid 3px red"
      document.getElementById("lbluser").style.visibility = "visible";
      return false;
    }
    else if (password.value.trim() == "") {
      alert("Blank Password");
      return false;
    }
    else if (password.value.trim().length < 5) {
      alert("Password must be at least five character long.");
      return false;
    }
    else if (password.value == password1.value && username.value == "Administrator") {
      alert("User login successful");
      return true;
    }
    else {
      alert("User login unsuccessful");
      console.log(password.value);
      console.log(password1.value);
      return false;
    }
  }
  function loadserverpage() {
    read_localserver();
    read_remoteserver();
  }
  function loadmqttpage() {
    read_mqtt();
    
  }
  function loadportsettingpage() {
    portoutputitemlist();
    portarealist()
    sortarea();
    sortItemname();
    selecttimertype();
    butsel();
    devcontrol();
    read_mac();
    filecheck()
    //loadportdata();
  }
  function butsel1()
  {
    console.log(document.getElementById("Itemname").value)

  }
  function loadpage() {
    fn1();
    sortarea();
    sortItemname();
    sortdetectedssid();
    read_stored_ssid();
    read_detected_ssid();
  }
  function loadwifipage() {
    fn1();
    sortdetectedssid();
    read_stored_ssid();
    read_detected_ssid();
  }
  function loadindex() {
    read_password();
  }

  
  function sortdetectedssid() {
    var list, i, switching, b, shouldSwitch;
    list = document.getElementById("detectedssid");
    switching = true;
    /* Make a loop that will continue until
    no switching has been done: */
    while (switching) {
      // start by saying: no switching is done:
      switching = false;
      b = list.getElementsByTagName("option");
      // Loop through all list-items:
      for (i = 0; i < (b.length - 1); i++) {
        // start by saying there should be no switching:
        shouldSwitch = false;
        /* check if the next item should
        switch place with the current item: */
        if (b[i].innerHTML.toLowerCase() > b[i + 1].innerHTML.toLowerCase()) {
          /* if next item is alphabetically
          lower than current item, mark as a switch
          and break the loop: */
          shouldSwitch = true;
          break;
        }
      }
      if (shouldSwitch) {
        /* If a switch has been marked, make the switch
        and mark the switch as done: */
        b[i].parentNode.insertBefore(b[i + 1], b[i]);
        switching = true;
      }
    }
  }
 
  function sortarea() {
    var list, i, switching, b, shouldSwitch;
    list = document.getElementById("area");
    switching = true;
    /* Make a loop that will continue until
    no switching has been done: */
    while (switching) {
      // start by saying: no switching is done:
      switching = false;
      b = list.getElementsByTagName("option");
      // Loop through all list-items:
      for (i = 0; i < (b.length - 1); i++) {
        // start by saying there should be no switching:
        shouldSwitch = false;
        /* check if the next item should
        switch place with the current item: */
        if (b[i].innerHTML.toLowerCase() > b[i + 1].innerHTML.toLowerCase()) {
          /* if next item is alphabetically
          lower than current item, mark as a switch
          and break the loop: */
          shouldSwitch = true;
          break;
        }
      }
      if (shouldSwitch) {
        /* If a switch has been marked, make the switch
        and mark the switch as done: */
        b[i].parentNode.insertBefore(b[i + 1], b[i]);
        switching = true;
      }
    }
  }


  function sortItemname() {
    var list, i, switching, b, shouldSwitch;
    list = document.getElementById("Itemname");
    switching = true;
    /* Make a loop that will continue until
    no switching has been done: */
    while (switching) {
      // start by saying: no switching is done:
      switching = false;
      b = list.getElementsByTagName("option");
      // Loop through all list-items:
      for (i = 0; i < (b.length - 1); i++) {
        // start by saying there should be no switching:
        shouldSwitch = false;
        /* check if the next item should
        switch place with the current item: */
        if (b[i].innerHTML.toLowerCase() > b[i + 1].innerHTML.toLowerCase()) {
          /* if next item is alphabetically
          lower than current item, mark as a switch
          and break the loop: */
          shouldSwitch = true;
          break;
        }
      }
      if (shouldSwitch) {
        /* If a switch has been marked, make the switch
        and mark the switch as done: */
        b[i].parentNode.insertBefore(b[i + 1], b[i]);
        switching = true;
      }
    }
  }
  function read_detected_ssid() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        var len = myObj.detected_ssid.length;
        if (len > 0) {
          for (var ii = 0; ii < myObj.detected_ssid.length; ii++) {

            var sto_ssid = myObj.detected_ssid[ii].ssid;
            var sto_pass = myObj.detected_ssid[ii].signal;
            var sto_prio = myObj.detected_ssid[ii].type;
            var table = document.getElementById("myTable1");
            var row = table.insertRow(ii + 1);
            var cell1 = row.insertCell(0);
            var cell2 = row.insertCell(1);
            var cell3 = row.insertCell(2);
            cell1.innerHTML = sto_ssid;
            cell2.innerHTML = sto_pass;
            cell3.innerHTML = sto_prio;
          }
        }
      }
    };
    xmlhttp.open("GET", "detectedssid.json", true);
    xmlhttp.send();
  }
  function portarealist()
  {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        var dev_name;
        var x = document.getElementById("area");
        var n = 1;
        while (n <= x.length) {
        console.log(n + "   " + x.length)
        x.remove(0);
        }
        var dev_count=myObj.devices_output.length;
        if (dev_count>0)
        {
          for (var ii = 0; ii < myObj.devices_output.length; ii++) {
            dev_name= myObj.devices_output[ii];
            console.log(dev_name + " " + ii);
            var option = document.createElement("option");
            option.text = dev_name;
            x.add(option);
          }
        } 
      }
    };
    xmlhttp.open("GET", "devicesarea.json", true);
    xmlhttp.send();
  }

  function portoutputitemlist()
  {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        var dev_name;
        var x = document.getElementById("Itemname");
        var n = 1;
        while (n <= x.length) {
        console.log(n + "   " + x.length)
        x.remove(0);
        }
        var dev_count=myObj.devices_output.length;
        if (dev_count>0)
        {
          for (var ii = 0; ii < myObj.devices_output.length; ii++) {
            dev_name= myObj.devices_output[ii];
            console.log(dev_name + " " + ii);
            var option = document.createElement("option");
            option.text = dev_name;
            x.add(option);
          }
        } 
      }
    };
    xmlhttp.open("GET", "devicesoutput.json", true);
    xmlhttp.send();
  }

  function portinputitemlist()
  {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        var dev_name;
        var x = document.getElementById("Itemname");
        var n = 1;
        while (n <= x.length) {
        console.log(n + "   " + x.length)
        x.remove(0);
        }
        var dev_count=myObj.devices_output.length;
        if (dev_count>0)
        {
          for (var ii = 0; ii < myObj.devices_output.length; ii++) {
            dev_name= myObj.devices_output[ii];
            console.log(dev_name + " " + ii);
            var option = document.createElement("option");
           
            option.text = dev_name;
            x.add(option);
          }
        }
      }
    };
    xmlhttp.open("GET", "devicesinput.json", true);
    xmlhttp.send();
  }


  function read_stored_ssid() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);

        var len = myObj.stored_ssid.length;
        if (len > 0) {
          for (var ii = 0; ii < myObj.stored_ssid.length; ii++) {

            var sto_ssid = myObj.stored_ssid[ii].ssid;
            var sto_pass = (myObj.stored_ssid[ii].password);
            var sto_prio = myObj.stored_ssid[ii].priority;
            var table = document.getElementById("myTable2");
            var row = table.insertRow(ii + 1);
            var cell1 = row.insertCell(0);
            var cell2 = row.insertCell(1);
            var cell3 = row.insertCell(2);
            cell1.innerHTML = sto_ssid;
            cell2.innerHTML = sto_pass;
            cell3.innerHTML = sto_prio;
          }
        }
      }
    };
    xmlhttp.open("GET", "storedssid.json", true);
    xmlhttp.send();
  }
  function read_password() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("loginpassword1").value = myObj.user_password;
      }
    };
    xmlhttp.open("GET", "sitedata.json", true);
    xmlhttp.send();
  }
  function read_mac() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("chip_site_id").innerHTML = myObj.mac_id;
        document.getElementById("housename").value = myObj.site_name;
      }
    };
    xmlhttp.open("GET", "sitedata.json", true);
    xmlhttp.send();
  }
  function read_gensett() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("macaddress").innerHTML = myObj.mac_id;
        document.getElementById("serialspeed").value = myObj.serial_speed;
        document.getElementById("sitename").value = myObj.site_name;
        document.getElementById("adminpassword").value = myObj.admin_password;
        document.getElementById("userpassword").value = myObj.user_password;
        document.getElementById("hotspotssidname").value = myObj.hotspot_name;
        document.getElementById("hotspotpassword").value = myObj.hotspot_password;
      }
    };
    xmlhttp.open("GET", "sitedata.json", true);
    xmlhttp.send();
  }
  function read_mqtt() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("mqtturllocal").value = myObj.lms_url;
        document.getElementById("mqttportnumlocal").value = myObj.lms_port;
        document.getElementById("mqttusernamelocal").value = myObj.lms_user_name;
        document.getElementById("mqttpasswordlocal").value = myObj.lms_password;
        document.getElementById("mqttenablelocal").value = myObj.lms_enabled;
        document.getElementById("mqtturlremote").value = myObj.rms_url;
        document.getElementById("mqttportnumremote").value = myObj.rms_port;
        document.getElementById("mqttusernameremote").value = myObj.rms_user_name;
        document.getElementById("mqttpasswordremote").value = myObj.rms_password;
        document.getElementById("mqttenableremote").value = myObj.rms_enabled;
        console.log(myObj.lms_auth + "   " + myObj.rms_auth)
        if (myObj.lms_auth == "0") {
          document.getElementById("Auth").checked = true;
          document.getElementById("Auth1").checked = false;
          document.getElementById("lblusna").style.visibility = "hidden";
          document.getElementById("mqttusernamelocal").style.visibility = "hidden";
          document.getElementById("lblpass").style.visibility = "hidden";
          document.getElementById("mqttpasswordlocal").style.visibility = "hidden";
          
          
        }
        else {
          document.getElementById("Auth1").checked = true;
          document.getElementById("Auth").checked = false;
          document.getElementById("lblusna").style.visibility = "visible";
          document.getElementById("mqttusernamelocal").style.visibility = "visible";
          document.getElementById("lblpass").style.visibility = "visible";
          document.getElementById("mqttpasswordlocal").style.visibility = "visible";
        }
        if (myObj.rms_auth == "0") {
          document.getElementById("Auth2").checked = true;
          document.getElementById("Auth3").checked = false;
          document.getElementById("lblusna1").style.visibility = "hidden";
          document.getElementById("mqttusernameremote").style.visibility = "hidden";
          document.getElementById("lblpass1").style.visibility = "hidden";
          document.getElementById("mqttpasswordremote").style.visibility = "hidden";

        }
        else {
          document.getElementById("Auth3").checked = true;
          document.getElementById("Auth2").checked = false;
          document.getElementById("lblusna1").style.visibility = "visible";
          document.getElementById("mqttusernameremote").style.visibility = "visible";
          document.getElementById("lblpass1").style.visibility = "visible";
          document.getElementById("mqttpasswordremote").style.visibility = "visible";
        }
      }
    };
    xmlhttp.open("GET", "mqtt.json", true);
    xmlhttp.send();
  }
  function read_localserver() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("serverurllocal").value = myObj.local_server.url;
        document.getElementById("serveraccesstokenlocal").value = myObj.local_server.access_token;
        document.getElementById("serverusernamelocal").value = myObj.local_server.user_name;
        document.getElementById("serverpasswordlocal").value = myObj.local_server.password;
        document.getElementById("serverenablelocal").value = myObj.local_server.enabled;
        console.log("enabled " + myObj.local_server.enabled);
      }
    };
    xmlhttp.open("GET", "server.json", true);
    xmlhttp.send();
  }
  function read_remoteserver() {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        document.getElementById("serverurlremote").value = myObj.remote_server.url;
        document.getElementById("serveraccesstokenremote").value = myObj.remote_server.access_token;
        document.getElementById("serverusernameremote").value = myObj.remote_server.user_name;
        document.getElementById("serverpasswordremote").value = myObj.remote_server.password;
        document.getElementById("serverenableremote").value = myObj.remote_server.enabled;
        console.log("enabled " + myObj.remote_server.enabled);
      }
    };
    xmlhttp.open("GET", "server.json", true);
    xmlhttp.send();
  }
  function loadport1data(filename) {
    var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function () {
      if (this.readyState == 4 && this.status == 200) {
        var myObj = JSON.parse(this.responseText);
        var da1 = myObj.port_no;
        var da2 = myObj.gpio;
        var da3 = myObj.enable_status;
        var da4 = myObj.control;
        var da5 = myObj.server;
        var da6 = myObj.type_of_pin;
        var da7 = myObj.speed;
        var da8 = myObj.connected_device;
        var da9 = myObj.area;
        var da10 = myObj.timer_type;
        var da11 = myObj.on_time;
        var da12 = myObj.off_time_duration;
        var da13 = myObj.days;
        var da14 = myObj.mqtt_topic;
        var table = document.getElementById("mystoredport");
        var row = table.insertRow();
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        var cell3 = row.insertCell(2);
        var cell4 = row.insertCell(3);
        var cell5 = row.insertCell(4);
        var cell6 = row.insertCell(5);
        var cell7 = row.insertCell(6);
        var cell8 = row.insertCell(7);
        var cell9 = row.insertCell(8);
        var cell10 = row.insertCell(9);
        var cell11 = row.insertCell(10);
        var cell12 = row.insertCell(11);
        var cell13 = row.insertCell(12);
        var cell14 = row.insertCell(13);
        cell1.innerHTML = da1;
        cell2.innerHTML = da2;
        cell3.innerHTML = da3;
        cell4.innerHTML = da4;
        cell5.innerHTML = da5;
        cell6.innerHTML = da6;
        cell7.innerHTML = da7;
        cell8.innerHTML = da8;
        cell9.innerHTML = da9;
        cell10.innerHTML = da10;
        cell11.innerHTML = da11;
        cell12.innerHTML = da12;
        cell13.innerHTML = da13;
        cell14.innerHTML = da14;

      }
    };
    xmlhttp.open("GET", filename, true);
    xmlhttp.send();
  }
  function doesFileExist(urlToFile) {
    var xhr = new XMLHttpRequest();
    xhr.open ('HEAD', urlToFile, false);
    xhr.send();

    if (xhr.status == "404") {
      return false;
    } else {
      return true;
    }
  }
  function filecheck() {
    for (i = 1; i < 7; i++) {
      filename = "port" + i + ".json";
      var result = doesFileExist(filename);
      if (result == true) {
        loadport1data(filename);
      } else {
        console.log(filename + " does not exists");
      }
    }
  }
  function loadportdata() {
    loadport1data();
  }