<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	if($_GET["search"]){
		$search = $_GET["search"];
		print "<b>Searched:</b> '" . $search . "'";
		print "<br/><br/>";
		$db_connection = create_connection("localhost", "cs143", "");
		//$db_selected = choose_db("TEST", $db_connection);
		$sanitized_search = sanitize_string($search, $db_connection);
	
		$searched_movie = sprintf("%s", $sanitized_search);
		$movie_query = "select * from Movie where title like '%$searched_movie%'";
		//print $movie_query . "<br/>";
		
		$movies = run_query($movie_query, $db_connection);
		print "<p>Movie Results (" . mysql_num_rows($movies) . ")</p>";
		print "<ul>";
		while ($movie_row = mysql_fetch_array($movies, MYSQL_ASSOC)){
			$movie_link = sprintf("movie.php?movie_id=%d", $movie_row['id']);
			printf("<li><a href='%s'>%s</a></li>", $movie_link, $movie_row["title"]);
		}
		print "</ul>";
		print "<br/>";

		$actor_names = explode(" ", $sanitized_search);
		$actor_base_query = "select * from Actor where first='%s'";
		$actor_query = sprintf($actor_base_query, $actor_names[0]);
		if (count($actor_names) > 1){
			$actor_base_query .= " and last='%s'";
			$actor_query = sprintf($actor_base_query, $actor_names[0], $actor_names[1]);
		}
		//print $actor_query . "<br/>";
		$actors = run_query($actor_query, $db_connection);
		print "<p>Actor Results (" . mysql_num_rows($actors) . ")</p>";
		print "<ul>";
		while ($actor_row = mysql_fetch_array($actors, MYSQL_ASSOC)){
			$actor_link = sprintf("actor.php?actor_id=%d", $actor_row['id']);
			printf("<li><a href='%s'>%s %s</a></li>", $actor_link, $actor_row["first"], $actor_row["last"]);
		}
		print "</ul>";
		print "<br/>";

		$director_names = explode(" ", $sanitized_search);
		$director_base_query = "select * from Director where first='%s'";
		$director_query = sprintf($director_base_query, $director_names[0]);
		if (count($director_names) > 1){
			$director_base_query .= " and last='%s'";
			$director_query = sprintf($director_base_query, $director_names[0], $director_names[1]);
		}
		//print $director_query . "<br/>";
		$directors = run_query($director_query, $db_connection);
		print "<p>Director Results (" . mysql_num_rows($directors) . ")</p>";
		print "<ul>";
		while ($director_row = mysql_fetch_array($directors, MYSQL_ASSOC)){
			$director_link = sprintf("director.php?director_id=%d", $director_row['id']);
			printf("<li><a href='%s'>%s %s</a></li>", $director_link, $director_row["first"], $director_row["last"]);
		}
		print "</ul>";
		print "<hr/>";



		close_connection($db_connection);
	}
	print "</body>";
?>