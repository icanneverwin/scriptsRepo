select distinct pe.name from movies mv, stars st, people pe where mv.id = st.movie_id and st.person_id = pe.id and pe.name != 'Kevin Bacon' and mv.id in (
select m.id from movies m, stars s, people p where m.id = s.movie_id and s.person_id = p.id and p.name = 'Kevin Bacon' and p.birth = 1958);