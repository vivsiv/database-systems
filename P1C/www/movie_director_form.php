<?php
	include 'header.php';
	print "<body>";

	if ($_GET['movie_title']){
		$movie_title = $_GET['movie_title'];
		print "<h2>Add Director to $movie_title";
	}
	else {
		$director_name = $_GET['director_name'];
		print "<h2>Add Movie for $director_name";
	}
?>

<form id="create_movie_director_form" action='create_movie_director.php' method='GET'>
	<input name="create_movie_director" type="hidden" value="true"/>
<?php
	if ($_GET['movie_id']){
		$movie_id = $_GET['movie_id'];
		print "<input type='text' name='movie_id' hidden='true' value='$movie_id'/>";
		print "<h4>Director Name (First and Last)</h4>";
		print "<input type='text' name='director_name'/>";
		print "<br/><br/>";
		print "<input type='submit' value='Add Director'/>";
	}
	else {
		$director_id = $_GET['director_id'];
		print "<input type='text' name='director_id' hidden='true' value='$director_id'/>";
		print "<h4>Movie Title</h4>";
		print "<input type='text' name='movie_title'/>";
		print "<br/><br/>";
		print "<input type='submit' value='Add Movie'/>";
	}
?>
</form>

<?php print "</body>" ?>