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
		h2{
			font-size:300%;
			text-align:center;
			color:white;
		}
		
		.user{
			position:absolute;
			top:30%;
			left:35%;
			font-size:150%;
			color:white;
		}
		
		
		</style>
		</head>
	<body>
		<h2>Login Page</h2>
		<a href="index.php" style="text-decoration:none; color:white; position:fixed; left:45%;bottom:30%;font-size:200%;"> back</a><br/><br/>
		<div class="user">
		<form action="checklogin.php" method="post">
		Username: <input type="text" name="username" required="required"/> <br/><br>
		 Password : <input type="password" name="password" required="required" /> <br/> <br/>
			<input type="submit" value="Login"/>
		</form>
	</body>
</html>