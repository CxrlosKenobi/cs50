SELECT AVG(rating) AS 'Average rating'
FROM ratings JOIN movies ON movies.id = ratings.movie_id
WHERE year = 2012;