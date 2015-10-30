<?php include 'header.php' ?>
<body>
	<h2>Create Movie</h2>
	<form id="create_movie_form" action='create_movie.php' method='GET'>
		<input name="create_movie" type="hidden" value="true"/>
		<h4>Title</h4>
		<input type="text" name="title"/>
		<h4>Year</h4>
		<input type="text" name="year"/>
		<h4>Rating</h4>
		<input type="text" name="rating"/>
		<h4>Company</h4>
		<input type="text" name="company"/>
		<br/><br/>
		<input type='submit' value='Create Movie'/>
	</form>
</body>