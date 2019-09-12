<?php

function afficheJoueurs($bd)
{
	try
	{
		$req = $bd->prepare('SELECT * FROM joueursEchec');
		$req->execute();
		
		$res = $req->fetch(PDO::FETCH_ASSOC);

		//Il y a au moins une ligne
		if($res)
		{
			echo '<table>' . "\n";
			
			//On affiche les en-têtes
			echo '<tr>'."\n";
			foreach($res as $c => $v)
				echo '<th>' . $c . '</th>';
			echo '</tr>'."\n";
	 
	 		do
			{
				//On affiche chaque ligne de résultat
				echo '<tr>'."\n";
				foreach($res as $v)
					echo '<td>' . $v . '</td>';
				echo '</tr>'."\n";
			}while($res = $req->fetch(PDO::FETCH_ASSOC));
			echo '</table>' . "\n";
		}
		else
			echo '<p>Aucun joueur dans la base de données </p>';
	}
	catch(PDOException $e)
	{
	  	// On termine le script en affichant le n de l'erreur ainsi que le message 
    	die('<div class="filtre"> Erreur : ' . $e->getMessage() . '</div></body></html>');
	}	
	echo '</table>'."\n";
}


function afficheJoueursSelonFiltre($bd,$filtres,$ordre)
{
	try
	{
		
		$sql = 'SELECT * FROM joueursEchec';
		if(isset($filtres[':signeNaissance']))
		{
			$sql .= ' WHERE Naissance ';
			if($filtres[':signeNaissance']==-1)
				$sql.= ' <= ';
			else if ($filtres[':signeNaissance']==0)
				$sql .= ' = ' ;
			else
				$sql .= ' >= ' ;
			$sql .= ':naissance';
			unset($filtres[':signeNaissance']);
		}
		if(isset($filtres[':pays']))
		{
			if(isset($filtres[':naissance']))
				$sql .= ' AND ';
			else
			 	$sql .= ' WHERE ';
			$sql .= 'Pays = :pays';
		}
		if($ordre=='Nom')
			$sql .= ' ORDER BY Nom, Prénom' ;
		else
			$sql .= ' ORDER BY ' . $ordre . ' DESC';
			
		$req = $bd->prepare($sql);
		foreach($filtres as $c => $v)
			$req->bindValue($c,$v);
		$req->execute();
	
		echo '<table>' . "\n";
		$res = $req->fetch(PDO::FETCH_ASSOC);

		//Il y a au moins une ligne
		if($res)
		{
			//On affiche les en-têtes
			echo '<tr>'."\n";
			foreach($res as $c => $v)
				echo '<th>' . $c . '</th>';
			echo '<th class="sansBordure"></th></tr>'."\n";		
				 
	 		do
			{
				echo '<tr>'."\n";
				foreach($res as $v)
					echo '<td>' . $v . '</td>';
				echo '<td class="sansBordure"><a href="supprimer.php?nom='.urlencode($res['Nom']).'&amp;prenom='. urlencode($res['Prénom']).'"><img src="supprimer.png" alt="suppr"/></a></td></tr>'."\n";
			}while($res = $req->fetch(PDO::FETCH_ASSOC));
		}
		else
			echo '<p>Aucun joueur dans la base de données </p>';
	}
	catch(PDOException $e)
	{
	  	// On termine le script en affichant le num de l'erreur ainsi que le message 
    	die('<p> Erreur PDO[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
	}	
	echo '</table>'."\n";
}

function genereOptionsSelectPays($bd)
{
	try
	{
		$req = $bd->prepare('SELECT DISTINCT Pays FROM joueursEchec ORDER BY Pays');
		$req->execute();
		while($res = $req->fetch(PDO::FETCH_NUM))
			echo '<option> '. $res[0] . '</option>'."\n";
	}
	catch(PDOException $e)
	{
	  	// On termine le script en affichant le num de l'erreur ainsi que le message 
    	die('<p> Erreur PDO[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
	}
}



function genereUrl($ordre)
{
	$_GET['ordre'] = $ordre;
	echo $_SERVER['PHP_SELF'] . '?';
	foreach($_GET as $c => $v){
		echo $c . '=' . urlencode($v) . '&';
    }
}


//Test si les valeurs du premier tableau ($cle) sont des clés du deuxième et si les valeurs ne sont pas vides
function testParam($cle,$tableau)
{
	foreach($cle as $v)
		if(!isset($tableau[$v]) or trim($tableau[$v])== '')
			return false;
	return true;
}

function afficheT($tab)
{
	echo '<pre>';
	print_r($tab);
	echo '</pre>';
}

function joueurExiste($bd,$nom,$prenom)
{
	try
	{
		$req = $bd->prepare('SELECT * FROM joueursEchec WHERE Nom = :nom AND Prénom = :prenom');
		$req->bindValue(':nom',$nom);
		$req->bindValue(':prenom',$prenom);
		$req->execute();
		return $req->fetch() != false;
	}
	catch(PDOException $e)
	{
		die('<p> Erreur PDO[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
	}
}


function afficheJoueursScore($bd,$score)
{
	try
	{
		$req = $bd->prepare('SELECT Nom, Prénom, Pays FROM joueursEchec WHERE Score = :score');
		$req->bindValue(':score',$score);
		$req->execute();
		while($res = $req->fetch(PDO::FETCH_ASSOC))
			echo '<p>'. $res['Nom'] . '  ' . $res['Prénom'] . ' (Pays : ' . $res['Pays'] . ')</p>'; 
	}
	catch(PDOException $e)
	{
		die('<p> Erreur PDO[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
	}
}

function scoreMaxMoyen($bd)
{
	$tab = array();
	try
	{
		$req = $bd->prepare('SELECT MAX(Score), AVG(Score) FROM joueursEchec');
		$req->execute();
		$res = $req->fetch(PDO::FETCH_NUM);
		$tab['max'] = $res[0];
		$tab['avg'] = $res[1];
		return $tab;
	}
	catch(PDOException $e)
	{
		die('<p> Erreur PDO[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
	}
}


?>
