<!DOCTYPE html>
<html>
<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	$db_connection = create_connection("localhost", "cs143", "");
	print "<h2>Movies! <a href='movie_form.php'>(Add)</a></h2>";
	$random_movies_query = "select * from Movie order by rand() limit 5";
	$random_movies = run_query($random_movies_query, $db_connection);
	print "<ul>";
	while ($random_movie_row = mysql_fetch_array($random_movies, MYSQL_ASSOC)){
		$movie_id = $random_movie_row['id'];
		$movie_tag = $random_movie_row['title'] . " " . $random_movie_row['rating'] . " (" . $random_movie_row['year'] . ")";
		$movie_link = "movie.php?movie_id=$movie_id";
		print "<li><a href=$movie_link>$movie_tag</a></li>";
	}
	print "</ul>";
	print "<hr/>";

	print "<h2>Actors! <a href='actor_form.php'>(Add)</a></h2>";
	$random_actors_query = "select * from Actor order by rand() limit 5";
	$random_actors = run_query($random_actors_query, $db_connection);
	print "<ul>";
	while ($random_actor_row = mysql_fetch_array($random_actors, MYSQL_ASSOC)){
		$actor_id = $random_actor_row['id'];
		$actor_tag = $random_actor_row['first'] . " " . $random_actor_row['last'] . " (" . $random_actor_row['dob'] . ")";
		$actor_link = "actor.php?actor_id=$actor_id";
		print "<li><a href=$actor_link>$actor_tag</a></li>";
	}
	print "</ul>";
	print "<hr/>";

	print "<h2>Directors! <a href='director_form.php'>(Add)</a></h2>";
	$random_directors_query = "select * from Director order by rand() limit 5";
	$random_directors = run_query($random_directors_query, $db_connection);
	print "<ul>";
	while ($random_director_row = mysql_fetch_array($random_directors, MYSQL_ASSOC)){
		$director_id = $random_director_row['id'];
		$director_tag = $random_director_row['first'] . " " . $random_director_row['last'] . " (" . $random_director_row['dob'] . ")";
		$director_link = "director.php?director_id=$director_id";
		print "<li><a href=$director_link>$director_tag</a></li>";
	}
	print "</ul>";

	print "<hr/>";
	close_connection($db_connection);
	print "</body>";
?>
</html>
