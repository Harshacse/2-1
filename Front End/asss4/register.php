<html>
	<head>
		<title>My first PHP website</title>
		<style>  
		
		
			body{
		argin:0;
padding:0;
background-image:url('y1.jpg');
background-repeat:no-repeat;
background-size:100%;
overflow: hidden;
			
			
		}
		
		h2{text-align : center;
	        color:white;	
			font-size:50px;
		
		}
		form{
			position:absolute;
			top:20%;
			left:37%;
			color:white;
			font-size:25px;
			
		}
		
		</style>
		<script>
         function check() {
    if(document.getElementById('password').value === document.getElementById('confirm_password').value) {
       
    } else {
         alert("password didnot match");  
		
		 
    }
}
     function check1() {
    if(document.getElementById('password').value === document.getElementById('confirm_password').value) {
       
    } else {
         alert("password didnot match");  
		
    }
}
  
   </script>

		
		
		
		
		
		  
		
		
	</head>
	
	<body>
	
		<h2>Registration Page</h2>
		<a href="index.php" style="position:absolute; bottom:20%; left:45%; font-size:40px; color:white; text-decoration:none;"> back</a><br/><br/>
		<form action="register.php" method="post"  onSubmit="return validate()";>
		    Enter Fullname : <input type="text" name="fullname" required="required"/> <br/><br>
			Enter Username: <input type="text" name="username" required="required"/> <br/><br>
			Enter Password : <input type="password" id="password" name="password" required="required" /> <br/><br>
		    Retype Password: <input type="password" name="confirm_password" id="confirm_password" onchange="check()"  required="required"/> 
<br/><br>
			<input type="submit" value="Register" style="position:relative; left:220px;"/>
		</form>
	</body>
</html>

<?php 
if($_SERVER["REQUEST_METHOD"] == "POST"){
	$username = mysql_real_escape_string($_POST['username']);
	$password = mysql_real_escape_string($_POST['password']);
	
    $bool = true;
	mysql_connect("mysql10.000webhost.com", "a2953611_madhu","madhusai3113") or die(mysql_error()); //Connect to server
	mysql_select_db("a2953611_firstdb") or die("Cannot connect to database"); //Connect to database
	$query = mysql_query("Select * from users"); //Query the users table
	while($row = mysql_fetch_array($query)) //display all rows from query
	{
		$table_users = $row['username']; // the first username row is passed on to $table_users, and so on until the query is finished
		if($username == $table_users ) // checks if there are any matching fields
		{
			$bool = false; // sets bool to false
			Print '<script>alert("Username has been taken!");</script>'; //Prompts the user
			Print '<script>window.location.assign("register.php");</script>'; // redirects to register.php
		}

		
	}
	if($bool) // checks if bool is true
	{
		mysql_query("INSERT INTO users (username, password) VALUES ('$username','$password')"); //Inserts the value to table users
		Print '<script>alert("Successfully Registered!");</script>'; // Prompts the user
		Print '<script>window.location.assign("register.php");</script>'; // redirects to register.php
	}
}
?>