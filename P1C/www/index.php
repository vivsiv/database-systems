<!DOCTYPE html>
<html>
	<head>
		<link rel="stylesheet" type="text/css" href="assets/style.css"/>
		<h1 class="title">Vivek's Movie Database</h1>
		<hr/>
	</head>
	<body>
		<h2>Search for Actor or Movie</h2>
		<form id="search_form" action='search.php' method='GET'>
			<textarea id='search' name='search'></textarea>
			<br/><br/>
			<input id='submit' type='submit' value='Search'/>
		</form>
		<hr/>

		<h2>Create Actor/Director</h2>
		<form id="create_person_form" action='create_person.php' method='GET'>
			<select id="create_person_select" name='create_person_select'>
				<option value="actor">Actor</option>
				<option value="director">Director</option>
			</select>
			<input name="create_person" type="hidden" value="true"/>
			<h4>First Name</h4>
			<input type="text" name="first"/>
			<h4>Last Name</h4>
			<input type="text" name="last"/>
			<h4>Sex</h4>
			<input type="text" name="sex"/>
			<h4>DOB</h4>
			<input type="text" name="dob"/>
			<h4>DOD</h4>
			<input type="text" name="dod"/>
			<br/><br/>
			<input id='submit' type='submit' value='Create Person'/>
		</form>
		<hr/>

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
			<input id='submit' type='submit' value='Create Movie'/>
		</form>
		<hr/>

		<h2>Add Actor or Director to Movie</h2>
		<form id="create_movie_person_form" action='create_movie_person.php' method='GET'>
			<input name="create_movie_person" type="hidden" value="true"/>
			<select id="create_movie_person_select" name='create_movie_person_select'>
				<option value="actor">Actor</option>
				<option value="director">Director</option>
			</select>
			<h4>Person Name (First and Last)</h4>
			<input type="text" name="person_name"/>
			<h4>Movie Title</h4>
			<input type="text" name="movie_title"/>
			<h4>Role (For Actors)</h4>
			<input type="text" name="role"/>
			<br/><br/>
			<input id='submit' type='submit' value='Create Movie Person'/>
		</form>
		<hr/>


	<?php
		include 'search.php'; 
		include 'create.php';
	?>
	</body>
</html>
