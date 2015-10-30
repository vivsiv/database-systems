<?php
	include 'header.php';
	print "<body>";

	if ($_GET['movie_title']){
		$movie_title = $_GET['movie_title'];
		print "<h2 class='form_header'>Add Director to $movie_title</h2>";
	}
	else {
		$director_name = $_GET['director_name'];
		print "<h2 class='form_header'>Add Movie for $director_name</h2>";
	}
?>

<form id="create_movie_director_form" action='create_movie_director.php' method='GET'>
	<input name="create_movie_director" type="hidden" value="true"/>
<?php
	if ($_GET['movie_id']){
		$movie_id = $_GET['movie_id'];
		print "<input type='text' name='movie_id' hidden='true' value='$movie_id'/>";
		print "<div>";
		print "<label class='form_label'>First Name: </label><input class='form_input_large' type='text' name='first'/>";
		print "<label class='form_label'>Last Name: </label><input class='form_input_large' type='text' name='last'/>";
		print "</div>";
		print "<br/><br/><br/><br/>";
		print "<input class='form_submit' type='submit' value='Add Director'/>";
	}
	else {
		$director_id = $_GET['director_id'];
		print "<input type='text' name='director_id' hidden='true' value='$director_id'/>";
		print "<div>";
		print "<label class='form_label'>Movie Title</label><input class='form_input_large' type='text' name='movie_title'/>";
		print "</div>";
		print "<br/><br/><br/><br/>";
		print "<input class='form_submit' type='submit' value='Add Movie'/>";
	}
?>
</form>

<?php print "</body>" ?>