let hour_ten_value = 0;
let hour_one_value = 0;
let minute_ten_value = 0;
let minute_one_value = 0;
let second_ten_value = 0;
let second_one_value = 0;

function increase_value(display_element){
   switch(display_element){
    case 'hour_ten_element':
        if(hour_ten_value<15){
            hour_ten_value++;
        }
        break;
    case 'hour_one_element':
        if(hour_one_value<15){
            hour_one_value++;
        }
        break;
    case 'minute_ten_element':
        if(minute_ten_value<15){
            minute_ten_value++;
        }
        break;
    case 'minute_one_element':
        if(minute_one_value<15){
            minute_one_value++;
        }
        break;
    case 'second_ten_element':
        if(second_ten_value<15){
            second_ten_value++;
        }
        break;
    case 'second_one_element':
        if(second_one_value<15){
            second_one_value++;
        }
        break;
    default:
        break;
   }
   update_values();
}

function decrease_value(display_element){
    switch(display_element){
        case 'hour_ten_element':
            if(hour_ten_value>0){
                hour_ten_value--;
            }
            break;
        case 'hour_one_element':
            if(hour_one_value>0){
                hour_one_value--;
            }
            break;
        case 'minute_ten_element':
            if(minute_ten_value>0){
                minute_ten_value--;
            }
            break;
        case 'minute_one_element':
            if(minute_one_value>0){
                minute_one_value--;
            }
            break;
        case 'second_ten_element':
            if(second_ten_value>0){
                second_ten_value--;
            }
            break;
        case 'second_one_element':
            if(second_one_value>0){
                second_one_value--;
            }
            break;
        default:
            break;
       }
       update_values();
    }

 function update_values(){
    document.getElementById("hour_ten_value").innerHTML = hour_ten_value;
    document.getElementById("hour_one_value").innerHTML = hour_one_value;
    document.getElementById("minute_ten_value").innerHTML = minute_ten_value;
    document.getElementById("minute_one_value").innerHTML = minute_one_value;
    document.getElementById("second_ten_value").innerHTML = second_ten_value;
    document.getElementById("second_one_value").innerHTML = second_one_value;
 }

 function check_value(value){
    return value;
 }

 function set_auto_time(){
    const now = new Date();
    hour_ten_value = Number((now.getHours()/10).toString().slice(0,-1));
    hour_one_value = now.getHours()%10;

    minute_ten_value = Number((now.getMinutes()/10).toString().slice(0,-1));
    minute_one_value = now.getMinutes()%10;

    second_ten_value = Number((now.getSeconds()/10).toString().slice(0,-1));
    second_one_value = now.getSeconds()%10;

    update_values();
    set_values();
 }

 function clear_values(){
    hour_ten_value = 0;
    hour_one_value = 0;
    minute_ten_value = 0;
    minute_one_value = 0;
    second_ten_value = 0;
    second_one_value = 0;

    update_values();
 }

 function set_values(){
    const json_output = {ht:hour_ten_value,ho:hour_one_value,mt:minute_ten_value,mo:minute_one_value,st:second_ten_value,so:second_one_value};

    fetch('/button-click', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify(json_output),
    })
    .then(response => response.text())
    .then(data => {
        console.log(data)
    })
    .catch(error => {
        console.error('Error:', error);
    });
    console.log(json_output);
 }