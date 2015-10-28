<?php
	include 'db_functions.php';
	if($_GET["search"]){
		$search = $_GET["search"];
		print "<b>Searched..</b>: '" . $search . "'";
		print "<br/><br/>";
		$db_connection = create_connection("localhost", "cs143", "");
		print $db_connection->host_info;
		print "<br/>";
		$db_selected = choose_db("TEST", $db_connection);
		$sanitized_search = sanitize_string($search, $db_connection);
	
		$searched_movie = sprintf("%s", $sanitized_search);
		$movie_query = "select * from Movie where title like '%$searched_movie%'";
		print $movie_query . "<br/>";

		$actor_names = explode(" ", $sanitized_search);
		$actor_base_query = "select * from Actor where first='%s'";
		$actor_query = sprintf($actor_base_query, $actor_names[0]);

		if (count($actor_names) > 1){
			$actor_base_query .= " and last='%s'";
			$actor_query = sprintf($actor_base_query, $actor_names[0], $actor_names[1]);
		}
		print $actor_query . "<br/>";
		
		$movies = run_query($movie_query, $db_connection);
		$actors = run_query($actor_query, $db_connection);

		print "<p>Movie Results (" . mysql_num_rows($movies) . ")</p>";
		print "<br/>";
		print "<ul>";
		while ($movie_row = mysql_fetch_array($movies, MYSQL_ASSOC)){
			printf("<li>%s</li>", $movie_row["title"]);
		}
		print "</ul>";
		print "<br/><br/>";
		print "<p>Actor Results (" . mysql_num_rows($actors) . ")</p>";
		print "<ul>";
		while ($actor_row = mysql_fetch_array($actors, MYSQL_ASSOC)){
			printf("<li>%s %s</li>", $actor_row["first"], $actor_row["last"]);
		}
		print "</ul>";
		print "<hr/>";

		close_connection($db_connection);
	}
?>