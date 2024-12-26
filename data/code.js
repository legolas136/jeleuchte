// function refreshColorpicker() {
// 	var s = document.getElementById("program");
// 	var a = document.getElementsByClassName("colorPicker")[0];
// 	var act_program = s.options[s.selectedIndex].value;
// 	var cp = document.getElementById("colorInputStatic");

// 	if (act_program != "6") {

// 		a.hidden = false;
// 		cp.jscolor.hide();
// 		a.hidden = true;

// 	}

// 	else {
// 		a.hidden = false;
// 		jscolor.install();
// 		cp.jscolor.show();

// 	}
// }

function sendVal(id, value) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/param?" + "id=" + id + "&value=" + value, true);
	xhr.send();
}

function sendClassVal(classx, id, value) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/param?" + "class=" + classx + "&id=" + id + "&value=" + value, true);
	xhr.send();
}

function sendWifiCred(isWifi, ssid_index, password) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/param?" + "iswifi=" + isWifi + "&ssid_index=" + ssid_index + "&password=" + password, true);
	xhr.send();
}



function sendRgb(id, r, g, b) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", "/param?" + "id=" + id + "&r=" + r + "&g=" + g + "&b=" + b, true);
	xhr.send();
}

function powerToggle(element) {
	var id = element.id;
	var value = element.value;

	sendVal(id, value);
}

function buttonPress(element) {
	var id = element.id;
	var value = element.value;

	sendVal(id, value);
}

function saveConfig() {
	var id = "save_config";
	var value = "1";

	sendVal(id, value);

	alert("Config Saved.")
}

function eraseConfig(element) {
	var id = element.id;
	var value = element.value;

	sendVal(id, value);

	alert("Config erased. WiFi Config still present :-)\nNote, that the credential for the access point have been resetted, also.")
}

function eraseWifiPrefs(element) {
	var id = element.id;
	var value = element.value;

	sendVal(id, value);

	alert("Wifi credentials erased.")
}

function updateColor(element) {
	var id = element.id;
	var r = Math.round(element.jscolor.channel('R'));
	var g = Math.round(element.jscolor.channel('G'));
	var b = Math.round(element.jscolor.channel('B'));
	// triggers 'onInput' and 'onChange' on all color pickers when they are ready
	jscolor.trigger(sendRgb(id, r, g, b));
	console.log(r, g, b);
}

function updateColorHsv1(element) {
	var id = 'colorInputGrad1';
	var h = element.channel('H');
	var s = element.channel('S');
	var v = element.channel('V');
	h = Math.round((h * 255) / 360);
	s = Math.round((s * 255) / 100);
	v = Math.round((v * 255) / 100);
	// triggers 'onInput' and 'onChange' on all color pickers when they are ready
	jscolor.trigger(sendRgb(id, h, s, v));
}

function updateColorHsv2(element) {
	var id = 'colorInputGrad2';
	var h = element.channel('H');
	var s = element.channel('S');
	var v = element.channel('V');
	h = Math.round((h * 255) / 360);
	s = Math.round((s * 255) / 100);
	v = Math.round((v * 255) / 100);
	// triggers 'onInput' and 'onChange' on all color pickers when they are ready
	jscolor.trigger(sendRgb(id, h, s, v));
}

function updateSlider(element) {
	var id = element.id;
	var name = element.name;
	var value = element.value;

	sendVal(id, value);
}

function updateSliderWClass(element) {
	var y = document.getElementsByClassName("bands_multi").item(element.name);
	var className = y.className;
	var name = element.name;
	var value = element.value;

	sendClassVal(className, name, value);
}

function selectSubmit(element) {
	var id = element.id;
	var name = element.name;
	var value = element.options[element.selectedIndex].value;
	if (element.id == "led_color_order") {
		alert("LED color order changed.\nConfig saved, restarting now!")
	}

	sendVal(id, value);
}

function toggleCheckbox(element) {
	var xhr = new XMLHttpRequest();
	var id = element.id;
	var value;
	if (element.checked) {
		value = 1;

	}
	else {
		value = 0;

	}

	sendVal(id, value);
}

function enterWifi(element) {
	var ssid = prompt("Enter SSID", "");
	if (ssid == null) {
		alert("No SSID given!");
		return
	}
	if (ssid.length > 32) {
		alert("SSID too long! (max is 32 characters!)");
		return
	}
	var wifipassword = prompt("Enter Password", "");
	if (wifipassword.length < 8) {
		alert("Password too short! (min is 8 characters!)");
		return
	}
	if (wifipassword.length > 64) {
		alert("Password too long! (max is 64 characters!)");
		return
	}
	alert("Wifi Credentials:\nSSID: " + ssid.toString() + "\nPassword: " + wifipassword.toString());
	alert("Trying to connect now.");

	var id = "ssid";
	sendVal(id, ssid);
	id = "password";
	sendVal(id, wifipassword);
}

function enterHostname(element) {
	var hostname = prompt("Enter Hostname", "");
	if (hostname == null) {
		alert("No hostname given!");
		return
	}
	if (hostname.length > 32) {
		alert("Hostname too long! (max is 32 characters!)");
		return
	}

	var id = element.id;
	sendVal(id, hostname);
}

function enterUpdateServer(element) {
	let uri = prompt("Enter Update Server URL", "http://your.server.com/firmware.bin");
	let encodedUri = encodeURI(uri);
	alert(encodedUri.toString());
	var id = element.id;
	sendVal(id, encodedUri);
}

function enterSpiffsServer(element) {
	let uri = prompt("Enter Spiffs Server URL", "http://your.server.com/spiffs.bin");
	let encodedUri = encodeURI(uri);
	alert(encodedUri.toString());
	var id = element.id;
	sendVal(id, encodedUri);
}

function enterAP(element) {
	var AP_ssid = prompt("Enter AP SSID", "xxx");
	if (AP_ssid == null) {
		alert("No SSID given!");
		return
	}
	if (AP_ssid > 32) {
		alert("SSID too long! (max is 32 characters!)");
		retun
	}
	if (AP_ssid == "") {
		alert("SSID may not be empty!");
		return
	}
	var AP_wifipassword = prompt("Enter AP Password", "xxxx");

	var id = "AP_ssid";
	sendVal(id, AP_ssid);
	id = "AP_password";
	sendVal(id, AP_wifipassword);
}

function enter_led_amount(element) {
	var led_amount = prompt("Enter Amount of LEDs.\nMaximum is 1024", "30");
	if (led_amount == null) {
		alert("No amount given!");
		return
	}
	if (led_amount > 1024) {
		alert("1024 LEDs max!");
		return
	}
	if (led_amount == "") {
		alert("LED amount may not be empty!");
		return
	}

	var id = "led_amount";
	sendVal(id, led_amount);
}

function reset() {
	var id = "reset"
	var value = "1"
	sendVal(id, value);
	setTimeout(function () {
		location.reload();
	}, 1000);

}

function printDebug(element) {
	sendVal(element.id, element.value);
}

function change_num_leds(element) {
	var num_leds = prompt("Enter number of LEDs:", "max. 300...");
	sendVal(element.id, num_leds);
}

function set_rf24_node_address(element) {
	var rf24_node_address = prompt("Enter Node Address in OCT format");
	sendVal(element.id, rf24_node_address);
}

function connect_to_wifi(element) {
	alert("fuction found");

	var isWifi = 1;
	var ssid_index = element.options[element.selectedIndex - 1].value;
	var password = prompt("Enter Password", "");

	sendWifiCred(isWifi, ssid_index, password);

	// saveConfig();
	// reset();


	// var ssid = element.id;
	// var name = element.name;
	// var value = element.options[element.selectedIndex].value;
	// var ssid = prompt("Enter SSID", "xxx");
	// if (ssid == null) {
	// 	alert("No SSID given!");
	// 	return
	// }
	// if (ssid > 32) {
	// 	alert("SSID too long! (max is 32 characters!)");
	// 	return
	// }
	// var wifipassword = prompt("Enter Password", "xxxx");

	// var id = "ssid";
	// sendVal(id, ssid);
	// id = "password";
	// sendVal(id, wifipassword);
}


function readFile(filePath) {
	var result = null;
	var xmlhttp = new XMLHttpRequest();
	xmlhttp.open("GET", filePath, false);
	xmlhttp.send();
	if (xmlhttp.status == 200) {
		result = xmlhttp.responseText;
	}
	return result;
}



function getText() {
	var text = document.getElementById("textareabox").value;
	alert(readFile("config.ini"));

}



function setText() {
	var x = readFile("config.ini");

	document.getElementById("textareabox").innerHTML = x;
	// var text = document.getElementById("textareabox").value = 'test';
}



function forceDownload(file_url, target_file_name) {
	var x = new XMLHttpRequest();
	x.open("GET", file_url, true);
	x.responseType = 'blob';
	x.onload = function (e) {
		saveAs(x.response, target_file_name, 'text/plain');
	};
	x.send();
}






function includeHTML() {
	var z, i, elmnt, file, xhttp;
	/*loop through a collection of all HTML elements:*/
	z = document.getElementsByTagName("*");
	for (i = 0; i < z.length; i++) {
		elmnt = z[i];
		/*search for elements with a certain atrribute:*/
		file = elmnt.getAttribute("w3-include-html");
		if (file) {
			/*make an HTTP request using the attribute value as the file name:*/
			xhttp = new XMLHttpRequest();
			xhttp.onreadystatechange = function () {
				if (this.readyState == 4) {
					if (this.status == 200) { elmnt.innerHTML = this.responseText; }
					if (this.status == 404) { elmnt.innerHTML = "Page not found."; }
					/*remove the attribute, and call this function once more:*/
					elmnt.removeAttribute("w3-include-html");
					includeHTML();
				}
			}
			xhttp.open("GET", file, true);
			xhttp.send();
			/*exit the function:*/
			return;
		}
	}
};

window.mobileCheck = function () {
	let check = false;
	(function (a) { if (/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino/i.test(a) || /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0, 4))) check = true; })(navigator.userAgent || navigator.vendor || window.opera);
	return check;
};