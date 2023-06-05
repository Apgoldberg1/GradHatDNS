const char index_html[] PROGMEM = R"rawliteral(
<html>

<style>
body {
  background: linear-gradient(45deg, #FC466B, #3F5EFB);
  height: 100vh;
  font-family: "Montserrat", sans-serif;
  overflow:hidden;
}

.container {
  position: absolute;
  transform: translate(-50%, -50%);
  top: 50%;
  left: 50%;
}

form {
  background: rgba(255, 255, 255, 0.3);
  padding: 2em;
  height: 500px;
  border-radius: 40px;
  border-left: 1px solid rgba(255, 255, 255, 0.3);
  border-top: 1px solid rgba(255, 255, 255, 0.3);

  box-shadow: 20px 20px 40px -6px rgba(0, 0, 0, 0.6);
  text-align: center;
  position: relative;
  transition: all 0.2s ease-in-out;
  border-color:rgba(255,255,255,.2);
  border-style: solid;
  border-width: 8px;
}
@media screen and (max-width: 1000px) and (min-height: 1000px) {
form{
transform: scale(2);
}
}

form p {
  font-weight: 500;
  color: #fff;
  opacity: 0.7;
  font-size: 2rem;
  margin-top: 20px;
  margin-bottom: 80px;
  text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
}
form input {
  background: transparent;
  width: 300px;
  padding: 1.5em;
  margin-bottom: 2em;
  border: none;
  border-left: 1px solid rgba(255, 255, 255, 0.3);
  border-top: 1px solid rgba(255, 255, 255, 0.3);
  border-radius: 5000px;
 
  box-shadow: 4px 4px 60px rgba(0, 0, 0, 0.2);
  color: #fff;
  font-family: Montserrat, sans-serif;
  font-weight: 500;
  transition: all 0.2s ease-in-out;
  text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.2);
}
form input:focus {
  box-shadow: 4px 4px 60px 8px rgba(0, 0, 0, 0.5);
}
::placeholder {
  font-family: Montserrat, sans-serif;
  font-weight: 400;
  color: #fff;
  text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.4);
  text-align: center;
}
#submit{
  background: linear-gradient(45deg, #FC466B, #3F5EFB);
  box-shadow: 4px 4px 60px rgba(0, 0, 0, 0.2);
}
</style>
<body>
    <div class="container">
    <form id="form" action="/">
        <br>
        <p>Welcome to my hat!</p>
        <br>
        <input type="text" name="message" maxlength="40" placeholder="Your Message Here">
        <br>
        <input id="submit" type="submit" value="Submit">
        <br>
        <br>
        <br>
        <br>
        <p><b>Thank you!</b></p>
    </form>
    </div>
</body>

</html>
)rawliteral";

const char proctor_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/proctoring">
    Code: <input type="text" name="code" maxlength="30">
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

const char messages_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/proctoring/approval">
    approval: <input type="text" name="code" maxlength="30">
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

const char resume_html[] PROGMEM = R"rawliteral(
  <html>
  <p>proofofconcept</p>
  </html>
)rawliteral";