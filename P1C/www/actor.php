<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	if ($_GET["actor_id"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$actor_id = intval(sanitize_string($_GET["actor_id"], $db_connection));
		$actor_base_query = "select * from Actor where id=%d";
		$actor_query = sprintf($actor_base_query, $actor_id);
		print $actor_query . "<br/>";
		$actor = run_query($actor_query, $db_connection);

		$actor_attr = mysql_fetch_array($actor, MYSQL_ASSOC);
		print "<ul>";
		printf("<li>%s %s</li>", $actor_attr["first"], $actor_attr["last"]);
		printf("<li>%s</li>", $actor_attr["sex"]);
		printf("<li>%s</li>", $actor_attr["dob"]);
		print "</ul>";
		print "<hr/>";

		$movie_actor_base_query = "select mid,role from MovieActor where aid=%d";
		$movie_actor_query = sprintf($movie_actor_base_query, $actor_id);
		print $movie_actor_query . "<br/>";
		$movie_actors = run_query($movie_actor_query, $db_connection);

		print "<p>Movies..</p>";
		$url_safe_actor_name = $actor_attr["first"] . "+" . $actor_attr["last"];
		$movie_actor_link = sprintf("movie_actor_form.php?actor_id=%d&actor_name=%s", $actor_id, $url_safe_actor_name);
		print "<p><a href=$movie_actor_link>Add a Movie for this Actor</a></p>";
		if (mysql_num_rows($movie_actors) > 0){
			$mids = array();
			$roles = array();
			while ($movie_actor_row = mysql_fetch_array($movie_actors, MYSQL_ASSOC)){
				array_push($mids,$movie_actor_row["mid"]);
				$roles[$movie_actor_row["mid"]] = $movie_actor_row["role"];
			}
			$mid_string = implode(",",$mids);
			$movie_base_query = "select * from Movie where id in (%s)";
			$movie_query = sprintf($movie_base_query, $mid_string);
			print $movie_query . "<br/>";
			$movies = run_query($movie_query, $db_connection);

			print "<ul>";
			while ($movie_row = mysql_fetch_array($movies, MYSQL_ASSOC)){
				$movie_link = sprintf("movie.php?movie_id=%d", intval($movie_row['id']));
				printf("<li><a href='%s'>%s as %s (%s) Rated: %s</a></li>", $movie_link, $movie_row["title"], $roles[$movie_row["id"]], $movie_row["year"], $movie_row["rating"]);
			}
			print "</ul>";
		}
		print "<hr/>";
		close_connection($db_connection);
	}
	print "</body>";

?>