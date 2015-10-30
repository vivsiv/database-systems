<?php
	include 'header.php';
	print "<body>";
	if ($_GET['movie_title']){
		$movie_title = $_GET['movie_title'];
		print "<h2 class='form_header'>Add Actor to $movie_title</h2>";
	}
	else {
		$actor_name = $_GET['actor_name'];
		print "<h2 class='form_header'>Add Movie for $actor_name</h2>";
	}
?>

<form id="create_movie_actor_form" action='create_movie_actor.php' method='GET'>
	<input name="create_movie_actor" type="hidden" value="true"/>
<?php
	if ($_GET['movie_id']){
		$movie_id = $_GET['movie_id'];
		print "<input type='text' name='movie_id' hidden='true' value='$movie_id'/>";
		print "<div>";
		print "<label class='form_label'>First Name: </label><input class='form_input_large' type='text' name='first'/><br/><br/>";
		print "<label class='form_label'>Last Name: </label><input class='form_input_large' type='text' name='last'/><br/><br/>";
		print "<label class='form_label'>Role: </label><textarea class='form_text_area' type='text' name='role'></textarea>";
		print "<br/><br/><br/><br/><br/><br/>";
		print "</div>";
		print "<input class='form_submit' type='submit' value='Add Actor'/>";
	}
	else {
		$actor_id = $_GET['actor_id'];
		print "<input type='text' name='actor_id' hidden='true' value='$actor_id'/>";
		print "<div>";
		print "<label class='form_label'>Movie Title: </label><input class='form_input' type='text' name='movie_title'/><br/><br/>";
		print "<label class='form_label'>Role: </label><textarea class='form_text_area' type='text' name='role'></textarea>";
		print "</div>";
		print "<br/><br/><br/><br/><br/><br/>";
		print "<input class='form_submit' type='submit' value='Add Movie'/>";
	}
?>
</form>

<?php print "</body>"; ?>