<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" type="text/css" href="assets/style.css"/>
		<h1 class="title">Vivek's Movie Database</h1>
		<hr/>
	</head>
	<body>
		<form id="search_form" action='search.php' method='GET'>
			<textarea id='search' name='search'></textarea>
			<br/><br/>
			<select id="search_select" name='search_select'>
				<option value="actor">Actor</option>
				<option value="director">Director</option>
				<option value="movie">Movie</option>
				<option></option>
			</select>
			<input id='submit' type='submit' value='Search'>
		</form>
		<hr/>
	<?php
		include 'search.php'; 
	?>
	</body>
</html>
