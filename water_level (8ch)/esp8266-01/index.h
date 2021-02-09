const char SITE_index[] PROGMEM = R"=====(
  <html>
   <head>
    <title>مؤشر مياه</title>
    <link rel="manifest" href="/manifest.webmanifest">
   </head>
   <body>
    <style>
body {
    background-color: #193c6d;

}
    .st0 {
      fill: none;
      stroke: #000000;
      stroke-width: 4;
      stroke-miterlimit: 5;
        
    }
    .st1 {
      fill: none;
      stroke: #000000;
       
      stroke-width: 3;
      stroke-miterlimit: 5;
    }
       
   
        
    #banner {
      border-radius: none;
     width: auto;
      height: 100%;
      background: none;
      overflow: hidden;
      backface-visibility: hidden;
      transform: translate3d(0, 0, 0);
      margin-top: auto;
        
      
       
        
    }
    #banner .fill {
      animation-name: fillAction;
      animation-iteration-count: infinite;
      animation-timing-function: cubic-bezier(.2, .6, .8, .4);
      animation-duration: 4s;
      animation-fill-mode: backwards;
    }
    #banner #waveShape_c {
      animation-name: waveAction;
      animation-iteration-count: infinite;
      animation-timing-function: linear;
      animation-duration: 1s;
      width: auto;
      height: 100%;
      fill: #04ACFF;
    }
         #banner #waveShape_h {
      animation-name: waveAction;
      animation-iteration-count: infinite;
      animation-timing-function: linear;
      animation-duration: 1s;
      width: auto;
      height: 100%;
      fill: #E31010 ;
    }

    @keyframes waveAction {
      0% {
        transform: translate(-150px, 0);
      }
      100% {
        transform: translate(0, 0);
      }
    }
  </style>

<script>
    document.addEventListener("DOMContentLoaded", getData);
     fill=document.getElementsByClassName("fill")
   var last="" 
   var map ={}
   var per={}
   
    map["6"]="0"
    map["5"]="31"
    map["4"]="53"
    map["3"]="70"
    map["2"]="107"
    map["1"]="128"
    map["0"]="150"
    
    per["6"]="100%"
    per["5"]="80%"
    per["4"]="60%"
    per["3"]="45%"
    per["2"]="30%"
    per["1"]="15%"
    per["0"]="0%"
    
function fill_fun(f1,l1,f2,l2){
  
       document.getElementById("1_per").innerHTML=per[l1].toString()
    document.getElementById("2_per").innerHTML=per[l2].toString()
    fill[0].animate([
  // keyframes
  { transform: 'translateY('+map[l1.toString()]+'px)' }, 
  { transform: 'translateY('+!parseInt(f1,10)*map[l1.toString()]+'px)' }
], { 
  // timing options
  duration: 4000,
  iterations: Infinity
});
   
    
    fill[1].animate([
  // keyframes
  { transform: 'translateY('+map[l2.toString()]+'px)' }, 
  { transform: 'translateY('+!parseInt(f2,10)*map[l2.toString()]+'px)' }
], { 
  // timing options
  duration: 4000,
  iterations: Infinity
});
               
}
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 5000); //2000mSeconds update rate

function getData() {
  t=document.getElementById("_table")
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
        response=this.responseText
     if (last.toString()!=response.toString())
      {
          last=response
          fill_fun(response[0],response[1],response[2],response[3])
           t.style.display=""
      }
      if (t.style.display.toString()=="none")
      {t.style.display=""}
    }else if (this.readyState == 4 && this.status !=200)
    {
        t.style.display="none"
      }
   
  };
  xhttp.open("GET", "read", true);
  xhttp.send();
}
</script>
  <table id="_table" style="height: 100%;width: 100%" cellpadding = "0" cellspacing = "0" >
      <tr>
          <td width="70%">
    <div id="banner" >
      <div>
        <svg version="1.1"  height="100%"   xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"  xml:space="preserve"  
           viewBox="0 0 200 200 " stroke="transparent" >

          <defs>
            <clipPath id="drop">
              <path transform="scale(0.75), translate(32,0)" d="M 68.2 6.7 C 68.2 6.7 5.8 77.6 5.8 131.4 C 5.8 163.7 33.8 189.8 68.2 189.8 S 130.6 163.6 130.6 131.4 C 130.7 77.6 68.3 6.7 68.2 6.7" />
            </clipPath>
          </defs>

          <g clip-path="url(#drop)">
            <g class="fill">
              <path fill="#04ACFF" id="waveShape_c" d="M300,300V2.5c0,0-0.6-0.1-1.1-0.1c0,0-25.5-2.3-40.5-2.4c-15,0-40.6,2.4-40.6,2.4
    c-12.3,1.1-30.3,1.8-31.9,1.9c-2-0.1-19.7-0.8-32-1.9c0,0-25.8-2.3-40.8-2.4c-15,0-40.8,2.4-40.8,2.4c-12.3,1.1-30.4,1.8-32,1.9
    c-2-0.1-20-0.8-32.2-1.9c0,0-3.1-0.3-8.1-0.7V300H300z" />
            </g>
          </g>
          <g transform="scale(0.75), translate(32,0)">
            <path class="st0" d="M68.2,6.7c0,0-62.4,70.9-62.4,124.7c0,32.3,28,58.4,62.4,58.4s62.4-26.2,62.4-58.4
    C130.7,77.6,68.3,6.7,68.2,6.7z" />
                         
          </g>
        </svg>         
      </div>
      </div>
      
     </td>
          <td width="30%">
          <p style="font-size:10vw; color: aliceblue;display: inline;"><b id="1_per"></b>
          </td>
      </tr>
      <tr>
          <td>
           <div id="banner">
      <div>
        <svg version="1.1" height="100%"   xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink"  xml:space="preserve"  
           viewBox="0 0 200 200 " stroke="transparent" >

          <defs>
            <clipPath id="drop">
              <path transform="scale(0.75), translate(32,0)" d="M 68.2 6.7 C 68.2 6.7 5.8 77.6 5.8 131.4 C 5.8 163.7 33.8 189.8 68.2 189.8 S 130.6 163.6 130.6 131.4 C 130.7 77.6 68.3 6.7 68.2 6.7" />
            </clipPath>
          </defs>

          <g clip-path="url(#drop)">
            <g class="fill">
              <path fill="#04ACFF" id="waveShape_h" d="M300,300V2.5c0,0-0.6-0.1-1.1-0.1c0,0-25.5-2.3-40.5-2.4c-15,0-40.6,2.4-40.6,2.4
    c-12.3,1.1-30.3,1.8-31.9,1.9c-2-0.1-19.7-0.8-32-1.9c0,0-25.8-2.3-40.8-2.4c-15,0-40.8,2.4-40.8,2.4c-12.3,1.1-30.4,1.8-32,1.9
    c-2-0.1-20-0.8-32.2-1.9c0,0-3.1-0.3-8.1-0.7V300H300z" />
            </g>
          </g>
          <g transform="scale(0.75), translate(32,0)">
            <path class="st0" d="M68.2,6.7c0,0-62.4,70.9-62.4,124.7c0,32.3,28,58.4,62.4,58.4s62.4-26.2,62.4-58.4
    C130.7,77.6,68.3,6.7,68.2,6.7z" />
                         
          </g>
        </svg>
          
      </div>
      </div>
              </td>
          <td >
          <p style="font-size:10vw; color: aliceblue;display: inline;"><b id="2_per"></b>
            
              </p>
          </td>
          </tr>
      </table>
                   
   </body>
  </html>
)=====";
