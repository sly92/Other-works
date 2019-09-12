<?php

try
{
	$login = ''; //A renseigner
	$mdp = ''; //A renseigner 
	$dsn = ''; //A renseigner
	$bd = new PDO($dsn,$login,$mdp);
	$bd->query('SET NAMES utf8');
  	$bd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
}
catch (PDOException $e)
{
   	// On termine le script en affichant le n de l'erreur ainsi que le message 
    die('<p> La connexion a échoué. Erreur[' .$e->getCode().'] : ' .$e->getMessage() . '</p>');
}
