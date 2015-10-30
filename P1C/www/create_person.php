<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	if($_GET["create_person"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$max_person_query = "select id from MaxPersonID order by id desc limit 1";
		$max_person_result = run_query($max_person_query, $db_connection);
		$old_max_person_id = intval(mysql_fetch_array($max_person_result, MYSQL_ASSOC)["id"]);
		
		$id = $old_max_person_id + 1;
		$first = sanitize_string($_GET["first"], $db_connection);
		$last = sanitize_string($_GET["last"], $db_connection);
		$sex = sanitize_string($_GET["sex"], $db_connection);
		$dob = intval(sanitize_string($_GET["dob"], $db_connection));
		$dod = NULL;
		if ($_GET["dod"]){
			$dod = intval(sanitize_string($_GET["dod"], $db_connection));
		}

		$person_type = sanitize_string($_GET["create_person_select"], $db_connection);
		print $person_type . "<br/>";
		if ($person_type == "actor"){
			$actor_base_query = "insert into Actor values (%d,'%s','%s','%s','%s','%s')";
			$actor_query = sprintf($actor_base_query, $id, $first, $last, $sex, $dob, $dod);
			print $actor_query . "<br/>";
			run_query($actor_query, $db_connection);
		}
		else if ($person_type == "director"){
			$director_base_query = "insert into Director values (%d,'%s','%s','%s','%s')";
			$director_query = sprintf($director_base_query, $id, $first, $last, $dob, $dod);
			print $director_query . "<br/>";
			run_query($director_query, $db_connection);
		}

		
		$max_person_update_query = sprintf("update MaxPersonID set id=%d where id=%d", $id, $old_max_person_id);
		print $max_person_update_query . "<br/>";
		run_query($max_person_update_query, $db_connection);
		close_connection($db_connection);
	}
	print "</body>";
?>