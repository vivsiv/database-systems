<?php
	include 'header.php';
	include 'db_functions.php';
	print '<body>';
	if($_GET['create_movie_director']){
		$db_connection = create_connection("localhost", "cs143", "");
		$movie_director_base_query = "insert into MovieDirector values (%d,%d)";
		$movie_id = NULL;
		$director_id = NULL;
		if ($_GET['movie_id']){
			$movie_id = sanitize_string($_GET['movie_id'], $db_connection);
			$director_name = sanitize_string($_GET['director_name'], $db_connection);
			$first = explode(" ", $director_name)[0];
			$last = explode(" ", $director_name)[1];
			$director_base_query = "select id from Director where first='%s' and last='%s'";
			$director_query = sprintf($director_base_query, $first, $last);
			print $director_query . "<br/>";
			$director = run_query($director_query, $db_connection);
			$director_row = mysql_fetch_array($director, MYSQL_ASSOC);
			$director_id = $director_row['id'];
		}
		else {
			$director_id = sanitize_string($_GET['director_id'], $db_connection);
			$movie_title = sanitize_string($_GET['movie_title'], $db_connection);
			$movie_base_query = "select id from Movie where title='%s'";
			$movie_query = sprintf($movie_base_query, $movie_title);
			print $movie_query . '<br/>';
			$movie = run_query($movie_query, $db_connection);
			$movie_row = mysql_fetch_array($movie, MYSQL_ASSOC);
			$movie_id = $movie_row['id'];
		}
		$movie_director_query = sprintf($movie_director_base_query, $movie_id, $director_id);
		print $movie_director_query . "<br/>";
		run_query($movie_director_query, $db_connection);
		close_connection($db_connection);
	}
	print "</body>";

?>