<?php
	include 'db_functions.php';
	if($_GET["create_movie"]) {
		$db_connection = create_connection("localhost", "cs143", "");
		$max_movie_query = "select id from MaxMovieID order by id desc limit 1";
		$max_movie_result = run_query($max_movie_query, $db_connection);
		$old_max_movie_id = intval(mysql_fetch_array($max_movie_result, MYSQL_ASSOC)["id"]);

		$id = $old_max_movie_id + 1;
		$title = sanitize_string($_GET["title"], $db_connection);
		$year = intval(sanitize_string($_GET["year"], $db_connection));
		$rating = sanitize_string($_GET["rating"], $db_connection);
		$company = sanitize_string($_GET["company"], $db_connection);
		$movie_base_query = "insert into Movie values (%d,'%s',%d,'%s','%s')";
		$movie_query = sprintf($movie_base_query, $id, $title, $year, $rating, $company);
		print $movie_query . "<br/>";
		run_query($movie_query, $db_connection);

		$max_movie_update_query = sprintf("update MaxMovieID set id=%d where id=%d", $id, $old_max_movie_id);
		print $max_movie_update_query . "<br/>";
		run_query($max_movie_update_query, $db_connection);
		close_connection($db_connection);
	}
?>