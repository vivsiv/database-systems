<?php
	if ($_GET['movie_title']){
		$movie_title = $_GET['movie_title'];
		print "<h2>Add Actor to $movie_title";
	}
	else {
		$actor_name = $_GET['actor_name'];
		print "<h2>Add Movie for $actor_name";
	}
?>

<form id="create_movie_actor_form" action='create_movie_actor.php' method='GET'>
	<input name="create_movie_actor" type="hidden" value="true"/>
<?php
	if ($_GET['movie_id']){
		$movie_id = $_GET['movie_id'];
		print "<input type='text' name='movie_id' hidden='true' value='$movie_id'/>";
		print "<h4>Actor Name (First and Last)</h4>";
		print "<input type='text' name='actor_name'/>";
		print "<h4>Role</h4>";
		print "<textarea type='text' name='role'></textarea>";
		print "<br/><br/>";
		print "<input id='submit' type='submit' value='Add Actor'/>";
	}
	else {
		$actor_id = $_GET['actor_id'];
		print "<input type='text' name='actor_id' hidden='true' value='$actor_id'/>";
		print "<h4>Movie Title</h4>";
		print "<input type='text' name='movie_title'/>";
		print "<h4>Role</h4>";
		print "<textarea type='text' name='role'></textarea>";
		print "<br/><br/>";
		print "<input id='submit' type='submit' value='Add Movie'/>";
	}
?>
</form>