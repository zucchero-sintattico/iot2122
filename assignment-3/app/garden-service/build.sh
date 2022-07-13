cp -R lib logic-component
cp -R lib serial-component
cp -R lib mqtt-component

if [ $# -eq 0 ]
  then
    docker compose up -d --build
    exit 0
fi

for service in "$@"
do
    docker compose up -d --build --no-deps $service
done

rm -rf logic-component/lib 
rm -rf serial-component/lib 
rm -rf mqtt-component/lib