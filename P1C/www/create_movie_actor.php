<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	if($_GET['create_movie_actor']){
		$db_connection = create_connection("localhost", "cs143", "");
		$movie_actor_base_query = "insert into MovieActor values (%d,%d,'%s')";
		$movie_id = NULL;
		$actor_id = NULL;
		if ($_GET['movie_id']){
			$movie_id = sanitize_string($_GET['movie_id'], $db_connection);
			$actor_name = sanitize_string($_GET['actor_name'], $db_connection);
			$first = explode(" ", $actor_name)[0];
			$last = explode(" ", $actor_name)[1];
			$actor_base_query = "select id from Actor where first='%s' and last='%s'";
			$actor_query = sprintf($actor_base_query, $first, $last);
			print $actor_query . "<br/>";
			$actor = run_query($actor_query, $db_connection);
			$actor_row = mysql_fetch_array($actor, MYSQL_ASSOC);
			$actor_id = $actor_row['id'];
		}
		else {
			$actor_id = sanitize_string($_GET['actor_id'], $db_connection);
			$movie_title = sanitize_string($_GET['movie_title'], $db_connection);
			$movie_base_query = "select id from Movie where title='%s'";
			$movie_query = sprintf($movie_base_query, $movie_title);
			print $movie_query . '<br/>';
			$movie = run_query($movie_query, $db_connection);
			$movie_row = mysql_fetch_array($movie, MYSQL_ASSOC);
			$movie_id = $movie_row['id'];
		}

		$role = sanitize_string($_GET["role"], $db_connection);
		$movie_actor_query = sprintf($movie_actor_base_query, $movie_id, $actor_id, $role);
		print $movie_actor_query . "<br/>";
		run_query($movie_actor_query, $db_connection);
		close_connection($db_connection);
	}
	print "</body>";

?>